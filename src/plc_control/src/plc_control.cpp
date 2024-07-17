#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "plc_control/plc.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include <unistd.h>

using std::placeholders::_1;
using namespace std::chrono_literals;

std::string plc_ip = "192.168.0.5";
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
        static int count = 0;
        
        if (message.compare("init") == 0 && count == 0)
		{
			plc.gateValve(on);
			plc_client("plc standby");
            plc.ioOnOff(pumpValveBig, off);
            plc.ioOnOff(pumpValveSmall, off);
            plc_client("plc standby");
			count = 1;
		}
		else if (message.compare("step 17") == 0 && count == 1)
		{
            plc.gateValve(off);
            usleep(1000 * 1000);
			plc.pump(on);
            plc.ioOnOff(buzz, on);
            usleep(1000 * 1000 * 3);
            plc.ioOnOff(buzz, off);
            usleep(1000 * 1000);
            plc.ioOnOff(arc, on);
            usleep(1000 * 1000 * 5);
            plc.ioOnOff(arc, off);
            usleep(1000 * 1000 * 2);
            plc.pump(off);
            plc.gateValve(on);
			plc_client("plc standby");
			count++;
		}
		else if (message.compare("finish") == 0)
		{
			count = 0;
		}

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
    }
    rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PlcSubscriber>());

    rclcpp::shutdown();
    return 0;
}