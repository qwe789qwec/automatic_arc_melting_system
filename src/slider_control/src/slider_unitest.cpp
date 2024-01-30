#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "slider_control/slider.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include <unistd.h>
#include <math.h>

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
	std::string center_x = slider.length2string(57*1000);
	std::string center_xy = slider.length2string(57*1000) + slider.length2string(30*1000);
	std::string center_yz = slider.length2string(30*1000) + slider.length2string(74.5*1000);// y 30 z 74.5
	// std::string center_yz = "0000753000012304";// y 30 z 74.5
	std::string zero = "0000000000000000";
	std::string home = "0001117000013880";// y 70 and z 80
	std::string route_1 = "0000EA60000124F8";// y 60 z 75
	std::string route_2 = "0000C35000011D28";// y 50 z 73
	std::string route_3 = "00009C4000011940";// y 40 z 72


	slider.move(motor_x, center_x, "08");// x 57
	slider.curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	usleep(1000 * 5000);
	slider.curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	slider.curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	slider.curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	slider.curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	

	int sep = 16;
	for(int i = 0; i < sep; i++){
		slider.curve_move(motor_x, motor_y, slider.count_circle(7000, sep, i, center_xy));
	}
	slider.move(motor_x, center_x, "08");// x 57
	slider.curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	slider.curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	slider.curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	slider.curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	slider.curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	// slider.move(motor_x, "0000EA60");


	rclcpp::spin(std::make_shared<SliderSubscriber>());

	rclcpp::shutdown();
	return 0;
}