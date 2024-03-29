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

int slider_client(std::string action)
{
	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("slider_process");
	rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr slider_process =
		node->create_client<msg_format::srv::ProcessService>("process_service");

	auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
	request->action = action;

	while (!slider_process->wait_for_service(1s))
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
		std::string message;
		message = msg->process;
        
        slider_client("slider ok");
	}
	rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	
	slider slider(slider_ip, slider_port);
	std::string center = "0000C3500000C350";
	std::string zero = "0000000000000000";
	slider.curve_move(motor4, motor5, "0000C3500000C350");
	std::string radius = slider.relative_position("0000C350", "00004E20", "-");
	std::string radius2 = slider.relative_position("0000C350", "00004E20", "+");
	std::string root2 = slider.relative_position("0000C350", "0000373E", "-");
	std::string root22 = slider.relative_position("0000C350", "0000373E", "+");
	slider.curve_move(motor4, motor5, "0000C350" + radius);
	slider.curve_move(motor4, motor5, root2 + root2);
	slider.curve_move(motor4, motor5, radius + "0000C350");
	slider.curve_move(motor4, motor5, root2 + root22);
	slider.curve_move(motor4, motor5, "0000C350" + radius2);
	slider.curve_move(motor4, motor5, root22 + root22);
	slider.curve_move(motor4, motor5, radius2 + "0000C350");
	slider.curve_move(motor4, motor5, root22 + root2);
	slider.curve_move(motor4, motor5, "0000C3500000C350");

	rclcpp::spin(std::make_shared<SliderSubscriber>());

	rclcpp::shutdown();
	return 0;
}