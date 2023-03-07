#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include <unistd.h>

#define arc_pos "00000000"
#define shelf_posA "000249F0"
#define shelf_posB "00041EB0"
#define shelf_posC "0005F370"
#define weighing_pos "0009C400"

using std::placeholders::_1;
using namespace std::chrono_literals;

std::string slider_ip = "192.168.0.3";
int slider_port = 64511;

std::string servo_onf(std::string station, std::string state)
{
	return "!99232" + station + state + "@@\r\n";
}
std::string servo_move(std::string station, std::string position)
{
	return "!99234" + station + "006400640064" + position + "@@\r\n";
}

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

void move_slider(std::string servo, std::string position)
{
	// std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
	char receive_msg[1024];
	tcp_socket slider_handler(slider_ip, slider_port);
	slider_handler.create();
	slider_handler.write(servo_onf(servo, "1"));
	slider_handler.receive(receive_msg);
	slider_handler.write(servo_move(servo, position));
	usleep(8000 * 1000);
	slider_handler.receive(receive_msg);
	slider_handler.write(servo_onf(servo, "0"));
	slider_handler.receive(receive_msg);
	slider_handler.end();
	usleep(1500 * 1000);
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
		// int head, end;
		message = msg->process;
		// RCLCPP_INFO(this->get_logger(), "I heard: '%s'", message.c_str());
		// head = message.find("slider");
		// if(head > 0){
		//   end = message.find("slider", head+3)
		//   end = end - head;
		//   action = message.substr(head + 7, end);
		//   slider_client(message);
		// }
		static int count = 0;
		if (message.compare("init") == 0 && count == 0)
		{
			move_slider("01", arc_pos);
			// move_slider("02", arc_pos);
			// move_slider("04", arc_pos);
			slider_client("slider ok");
			count = 2;
		}
		else if (message.compare("step 2") == 0 && count == 1)
		{
			move_slider("01", weighing_pos);
			slider_client("slider ok");
			count++;
		}
		else if (message.compare("step 4") == 0 && count == 2)
		{
			move_slider("01", weighing_pos);
			slider_client("slider ok");
			count++;
		}
		else if (message.compare("step 6") == 0 && count == 3)
		{
			move_slider("01", shelf_posA);
			slider_client("slider ok");
			count++;
		}
		else if (message.compare("step 8") == 0 && count == 4)
		{
			move_slider("01", shelf_posB);
			slider_client("slider ok");
			count++;
		}
		else if (message.compare("step 10") == 0 && count == 5)
		{
			move_slider("01", weighing_pos);
			slider_client("slider ok");
			count++;
		}
		else if (message.compare("step 14") == 0 && count == 6)
		{
			move_slider("01", arc_pos);
			slider_client("slider ok");
			count++;
		}
		else if (message.compare("Standby") == 0)
		{
			count = 0;
		}
	}
	rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<SliderSubscriber>());

	rclcpp::shutdown();
	return 0;
}