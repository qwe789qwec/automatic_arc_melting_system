#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include <unistd.h>

#define arc_pos "00000000"
#define shelf_pos "000249F0"
#define weighing_pos "0009C400"

using std::placeholders::_1;
using namespace std::chrono_literals;

std::string slider_ip = "192.168.0.3";
int slider_port = 64511;

std::string servo_onf(std::string station, std::string state){
  return "!99232" + station + state + "@@\r\n";
}
std::string servo_move(std::string station, std::string position){
  return "!99234" + station + "006400640064" + position + "@@\r\n";
}

int slider_client(std::string action){
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("slider_process");
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr slider_process =
        node->create_client<msg_format::srv::ProcessService>("process_service");

    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;

    while (!slider_process->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
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
    } else {
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
      if(message.compare("init") == 0 && count == 0){
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
        char receive_msg[1024];
        tcp_socket slider_handler(slider_ip, slider_port);
        slider_handler.create();
        slider_handler.write(servo_onf("01", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("02", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("04", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("01", arc_pos));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("02", arc_pos));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("04", arc_pos));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("07", "0"));
        slider_handler.receive(receive_msg);
        slider_handler.end();
        slider_client("slider ok");
        usleep(1500*1000);
        count++;
      }
      else if(message.compare("step one") == 0 && count == 1){
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
        char receive_msg[1024];
        tcp_socket slider_handler(slider_ip, slider_port);
        slider_handler.create();
        slider_handler.write(servo_onf("01", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("01", weighing_pos));
        usleep(8000*1000);
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("01", "0"));
        slider_handler.receive(receive_msg);
        slider_handler.end();
        slider_client("slider ok");
        usleep(1500*1000);
        count++;
      }
      else if(message.compare("step three") == 0 && count == 2){
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
        char receive_msg[1024];
        tcp_socket slider_handler(slider_ip, slider_port);
        slider_handler.create();
        slider_handler.write(servo_onf("01", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("01", shelf_pos));
        usleep(5000*1000);
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("01", "0"));
        slider_handler.receive(receive_msg);
        slider_handler.end();
        slider_client("slider ok");
        usleep(1500*1000);
        count++;
      }
      else if(message.compare("step six") == 0 && count == 3){
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
        char receive_msg[1024];
        tcp_socket slider_handler(slider_ip, slider_port);
        slider_handler.create();
        slider_handler.write(servo_onf("01", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("01", weighing_pos));
        usleep(5000*1000);
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("01", "0"));
        slider_handler.receive(receive_msg);
        slider_handler.end();
        slider_client("slider ok");
        usleep(1500*1000);
        count++;
      }
      else if(message.compare("step nine") == 0 && count == 4){
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
        char receive_msg[1024];
        tcp_socket slider_handler(slider_ip, slider_port);
        slider_handler.create();
        slider_handler.write(servo_onf("01", "1"));
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_move("01", arc_pos));
        usleep(8000*1000);
        slider_handler.receive(receive_msg);
        slider_handler.write(servo_onf("01", "0"));
        slider_handler.receive(receive_msg);
        slider_handler.end();
        slider_client("slider ok");
        usleep(1500*1000);
        count++;
      }
      else if(message.compare("Standby") == 0){
        count = 0;
      }
    }
    rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SliderSubscriber>());

    rclcpp::shutdown();
    return 0;
}