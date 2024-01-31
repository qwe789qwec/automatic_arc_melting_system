#include <chrono>
#include <cstdlib>
#include <memory>
#include <iomanip>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "plc_control/plc.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include <unistd.h>

using std::placeholders::_1;
using namespace std::chrono_literals;

std::string plc_ip = "192.168.0.4";
int plc_port = 9528;
plc plc(plc_ip, plc_port);

int plc_client(std::string action)
{
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("plc_process");
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr plc_process =
        node->create_client<msg_format::srv::ProcessService>("process_service");

    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;

    while (!plc_process->wait_for_service(1s))
    {
        if (!rclcpp::ok())
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return -1;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = plc_process->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "result: %s", result.get()->result.c_str());
    }
    else
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
        return -1;
    }
    return 0;
}

class PlcSubscriber : public rclcpp::Node
{
public:
    PlcSubscriber()
        : Node("plc_subscriber")
    {
        subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
            "topic", 10, std::bind(&PlcSubscriber::topic_callback, this, _1));
    }

private:
    void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg) const
    {
        std::string message = msg->process;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", message.c_str());
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
    }
    rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    // [00 01 00 00 00 06 00 05 00 0B FF 00] //turn buzz on
    // [00 01 00 00 00 06 00 05 00 0B 00 00] //turn buzz off

    // const char* buzz_on = "\x00\x01\x00\x00\x00\x06\x00\x05\x00\x0B\xFF\x00";
    // const char* buzz_off = "\x00\x01\x00\x00\x00\x06\x00\x05\x00\x0B\x00\x00";
    // sd0 start from 20480 sd1 equal to 20481 sd6180 equal to 26660
    const char* water_on = "\x00\x01\x00\x00\x00\x06\x00\x05\x00\x04\xFF\x00";
    const char* water_off = "\x00\x01\x00\x00\x00\x06\x00\x05\x00\x04\x00\x00";

    // const char* read_X = "\x00\x01\x00\x00\x00\x06\x00\x02\x00\x03\x00\x01";
    const char* read_SD = "\x00\x01\x00\x00\x00\x06\x00\x03\x68\x24\x00\x01";
    // const char* read_D = "\x00\x01\x00\x00\x00\x06\x00\x02\x00\x03\x00\x01";
    const char* write_SD500 = "\x00\x01\x00\x00\x00\x06\x00\x06\x68\x24\x01\xF4";
    const char* write_SD0 = "\x00\x01\x00\x00\x00\x06\x00\x06\x68\x24\x00\x00";
    
    char* return_message;
    std::cout << "write" << std::endl;
    int message_size = 12;
    return_message = plc.write_raw(water_on, message_size);
    std::cout << message_size << std::endl;
    for (int i = 0; i < message_size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(return_message[i])) << " ";
    }
    std::cout << std::endl;
    usleep(1000 * 1000 * 3);
    message_size = 12;
    return_message = plc.write_raw(water_off, message_size);
    std::cout << message_size << std::endl;
    for (int i = 0; i < message_size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(return_message[i])) << " ";
    }
    std::cout << std::endl;

    message_size = 12;
    return_message = plc.write_raw(write_SD500, message_size);
    std::cout << message_size << std::endl;
    for (int i = 0; i < message_size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(return_message[i])) << " ";
    }

    message_size = 12;
    return_message = plc.write_raw(read_SD, message_size);
    std::cout << message_size << std::endl;
    for (int i = 0; i < message_size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(return_message[i])) << " ";
    }
    usleep(1000 * 1000 * 3);

    message_size = 12;
    return_message = plc.write_raw(write_SD0, message_size);
    std::cout << message_size << std::endl;
    for (int i = 0; i < message_size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(return_message[i])) << " ";
    }
    std::cout << "finish test" << std::endl;

    // plc.pump(on);
    // plc.ioOnOff(buzz, on);
    // usleep(1000 * 1000 * 3);
    // plc.ioOnOff(buzz, off);
    // usleep(1000 * 1000);
    // plc.ioOnOff(arc, on);
    // usleep(1000 * 1000 * 5);
    // plc.ioOnOff(arc, off);
    // usleep(1000 * 1000 * 2);
    // plc.pump(off);



    rclcpp::spin(std::make_shared<PlcSubscriber>());

    rclcpp::shutdown();
    return 0;
}