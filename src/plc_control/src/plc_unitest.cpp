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

void printchar(const char *message, int size)
{   
    std::cout << "size:" << std::dec << size << " message:";
    for (int i = 0; i < size; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(message[i])) << " ";
    }
    std::cout << std::endl;
}

char* modbus(const char* function,const char* component,const char* data)
{
    // Allocate memory for the message
    static char message[] = "\x00\x01\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00";
    message[7] = function[0];
    message[8] = component[0];
    message[9] = component[1];
    message[10] = data[0];
    message[11] = data[1];

    return message;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    if(argv[1] == NULL){
        std::cout << "Please enter the weight" << std::endl;
        return 0;
    }

    std::string action = argv[1];
    char* return_message;

    if (action == "pump"){
        std::cout << "pump start" << std::endl;
        return_message = plc.coilWrite(M10, coilOn);
        usleep(1000 * 1000);
        return_message = plc.coilWrite(M10, coilOff);
    }
    else if(action == "vent"){
        std::cout << "vent start" << std::endl;
        return_message = plc.coilWrite(M15, coilOn);
        usleep(1000 * 1000);
        return_message = plc.coilWrite(M15, coilOff);
    }
    else if(action == "waterOn"){
        std::cout << "water start" << std::endl;
        return_message = plc.coilWrite(water0x, coilOn);
    }
    else if(action == "waterOff"){
        std::cout << "water off" << std::endl;
        return_message = plc.coilWrite(water0x, coilOff);
    }
    else if(action == "buzz"){
        std::cout << "buzz start" << std::endl;
        return_message = plc.coilWrite(buzz0x, coilOn);
        usleep(1000 * 1000 * 3);
        return_message = plc.coilWrite(buzz0x, coilOff);
    }
    else if(action == "gateOpen"){
        std::cout << "gate start" << std::endl;
        return_message = plc.coilWrite(openGateValve0x, coilOn);
        usleep(1000 * 1000);
        return_message = plc.coilWrite(openGateValve0x, coilOff);
    }
    else if(action == "gateClose"){
        std::cout << "gate start" << std::endl;
        return_message = plc.coilWrite(closeGateValve0x, coilOn);
        usleep(1000 * 1000);
        return_message = plc.coilWrite(closeGateValve0x, coilOff);
    }
    else if(action == "airOn"){
        std::cout << "air start" << std::endl;
        return_message = plc.coilWrite(airFlow0x, coilOn);
    }
    else if(action == "airOff"){
        std::cout << "air off" << std::endl;
        return_message = plc.coilWrite(airFlow0x, coilOff);
    }
    else if(action == "checkEMG"){
        std::cout << "check EMG" << std::endl;
        if(plc.inputRead(EMG)){
            std::cout << "EMG on" << std::endl;
        }
        else{
            std::cout << "EMG off" << std::endl;
        }
    }
    else if(action == "checkPresure"){
        std::cout << "check presure" << std::endl;
        if(plc.coilRead(s12coil)){
            std::cout << "In s12" << std::endl;
        }
        else{
            std::cout << "not in S12" << std::endl;
        }
    }

    printchar(return_message, 12);

    // [00 01 00 00 00 06 00 05 00 0B FF 00] //turn buzz on
    // [00 01 00 00 00 06 00 05 00 0B 00 00] //turn buzz off
    // const char* buzz_on = "\x00\x01\x00\x00\x00\x06\x00\x05\x00\x0B\xFF\x00";
    // const char* buzz_off = "\x00\x01\x00\x00\x00\x06\x00\x05\x00\x0B\x00\x00";

    // sd0 start from 20480 sd1 equal to 20481 sd6180 equal to 26660 sd6180 for analog

    // const char* read_X = "\x00\x01\x00\x00\x00\x06\x00\x02\x00\x03\x00\x01";
    // const char* read_SD = "\x00\x01\x00\x00\x00\x06\x00\x03\x03\x18\x00\x01";
    // const char* read_D = "\x00\x01\x00\x00\x00\x06\x00\x02\x00\x03\x00\x01";
    // const char* write_SD500 = "\x00\x01\x00\x00\x00\x06\x00\x06\x03\x18\x01\xF4";
    // const char* write_SD0 = "\x00\x01\x00\x00\x00\x06\x00\x06\x03\x18\x00\x00";

    // int message_size = 12;
    // std::cout << "analog on" << std::endl;
    // return_message = plc.writeRaw(modbus("\x06", sd61800x, "\x01\xF4"), message_size);
    // return_message = plc.registerWrite(sd61800x, 500);

    // message_size = 12;
    // std::cout << "analog read" << std::endl;
    // usleep(1000 * 500);
    // return_message = plc.writeRaw(modbus("\x03", sd61800x, "\x00\x01"), message_size);
    // if(plc.registerRead(sd61800x, 500)){
    //     std::cout << "read success" << std::endl;
    // }
    // else{
    //     std::cout << "read fail" << std::endl;
    // }
    // usleep(1000 * 1000 * 6);

    // std::cout << "analog off" << std::endl;
    // return_message = plc.registerWrite(sd61800x, 0);

    // std::cout << "finish test" << std::endl;

    rclcpp::spin(std::make_shared<PlcSubscriber>());

    rclcpp::shutdown();
    return 0;
}