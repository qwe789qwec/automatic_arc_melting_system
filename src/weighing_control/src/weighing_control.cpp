#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process.hpp"
#include "msg_format/srv/process_format.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

int weighing_client(std::string action){
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("weighing_process");
    int count = std::stoi(action);
    rclcpp::Client<msg_format::srv::ProcessFormat>::SharedPtr plc_process =
        node->create_client<msg_format::srv::ProcessFormat>("process_format");
    
    if(count > 60){
        action = "three";
    }
    else if(count > 40){
        action = "two";
    }
    else if(count > 20){
        action = "one";
    }
    else{
        action = "init";
    }

    auto request = std::make_shared<msg_format::srv::ProcessFormat::Request>();
    request->action = action;

    while (!plc_process->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
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
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
        return -1;
    }
    return 0;
}

class WeighingSubscriber : public rclcpp::Node
{
  public:
    WeighingSubscriber()
    : Node("weighing_subscriber")
    {
      subscription_ = this->create_subscription<msg_format::msg::Process>(
      "topic", 10, std::bind(&WeighingSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const msg_format::msg::Process::SharedPtr msg) const
    {
      std::string message = msg->process;
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", message.c_str());
      if(message.rfind("init", 0) == 0){
        message = message.substr(5);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
        weighing_client(message);
      }
      else if(message.rfind("keep", 0) == 0){
        message = message.substr(5);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
        weighing_client(message);
      }
      else if(message.rfind("first", 0) == 0){
        message = message.substr(7);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
        weighing_client(message);
      }
      else{
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());
        weighing_client("0");
      }
    }
    rclcpp::Subscription<msg_format::msg::Process>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WeighingSubscriber>());

    rclcpp::shutdown();
    return 0;
}