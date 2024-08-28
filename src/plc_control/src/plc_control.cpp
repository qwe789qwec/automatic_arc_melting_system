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
		static std::string step = "plc init";

		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step: %s", step.c_str());
		
		if(message.compare(step) != 0){
			step = message;
			RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step message: %s", message.c_str());
			bool action_result = plc.make_action(message);
			if(!action_result){
				RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "error cannot make action");
			}
			else{
				plc_client("plc standby");
			}
		}
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
    bool test = false;
	if (argc == 2 && test == true)
	{
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start test");
	}
	
	if (test){
		test = false;
		std::string test_action = "plc " + std::string(argv[1]);
		printf("test action: %s\n", test_action.c_str());
		plc.make_action(test_action);
	}

    // printchar(return_message, 12);

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PlcSubscriber>());

    rclcpp::shutdown();
    return 0;
}