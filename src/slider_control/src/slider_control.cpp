#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "slider_control/slider.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include <unistd.h>

using std::placeholders::_1;
using namespace std::chrono_literals;

std::string slider_ip = "192.168.0.3";
int slider_port = 64511;
slider slider(slider_ip, slider_port);

int slider_client(std::string action)
{
	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("slider_process");
	rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr slider_process =
		node->create_client<msg_format::srv::ProcessService>("process_service");

	auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
	request->action = action;

	while (!slider_process->wait_for_service(3s))
	{
		if (!rclcpp::ok())
		{
			RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
			return -1;
		}
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
	}

	auto result = slider_process->async_send_request(request);
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

class SliderSubscriber : public rclcpp::Node
{
public:
	SliderSubscriber()
		: Node("Slider_subscriber")
	{
		subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
			"topic", 10, std::bind(&SliderSubscriber::topic_callback, this, _1));
	}

private:
	void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg) const
	{
		std::string message = msg->process;
		static std::string step = "slider init";

		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step: %s", step.c_str());
		
		if(message.compare(step) != 0){
			step = message;
			RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step message: %s", message.c_str());
			bool action_result = slider.make_action(message);
			if(!action_result){
				RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "error cannot make action");
			}
			else{
				slider_client("slider standby");
			}
		}
	}
	rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{	
	bool test = false;
	if (argc == 2 && test == true)
	{
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start test");
	}
	
	if (test){
		test = false;
		std::string test_action = "slider " + std::string(argv[1]);
		printf("test action: %s\n", test_action.c_str());
		slider.make_action(test_action);
	}

	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<SliderSubscriber>());
	rclcpp::shutdown();
	return 0;
}