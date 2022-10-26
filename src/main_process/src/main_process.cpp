#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

std::string step = "init";

void process(const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
          std::shared_ptr<msg_format::srv::ProcessService::Response>      response)
{
  std::string action = request->action;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
  static bool slider = false;
  static bool weighing = false;
  static bool cobotta = false;

  if(action.compare("slider ok") == 0){
    slider = true;
  }
  if(action.compare("weighing ok") == 0){
    weighing = true;
  }
  if(action.compare("cobotta ok") == 0){
    cobotta = true;
  }

  if(step.compare("init") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step one";
      slider = false;
      weighing = false;
    }
  }
  else if(step.compare("step one") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step two";
      cobotta = false;
    }
  }
  else if(step.compare("step two") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step three";
      slider = false;
      weighing = false;
    }
  }
  else if(step.compare("step three") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step four";
      cobotta = false;
    }
  }
  else if(step.compare("step four") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step five";
      cobotta = false;
    }
  }
  else if(step.compare("step five") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step six";
      slider = false;
      weighing = false;
    }
  }
  else if(step.compare("step six") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step seven";
      cobotta = false;
    }
  }
  else if(step.compare("step seven") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step eight";
      cobotta = false;
    }
  }
  else if(step.compare("step eight") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step nine";
      slider = false;
      weighing = false;
    }
  }
  else if(step.compare("step nine") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "step ten";
      cobotta = false;
    }
  }
  else if(step.compare("step ten") == 0){
    if(slider && weighing && cobotta){
      response->result = "OK";
      step = "Standby";
    }
  }
  else{
    response->result = action;
    response->result = "OK";
    // step = "init";
  }
  response->result = "OK";
}

struct MainPublisher : public rclcpp::Node
{
  MainPublisher(const std::string & name, const std::string & output)
  : Node(name, rclcpp::NodeOptions().use_intra_process_comms(true))
  {
    // Create a publisher on the output topic.
    pub_ = this->create_publisher<msg_format::msg::ProcessMsg>(output, 10);
    std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;
    // Create a timer which publishes on the output topic at ~1Hz.
    auto callback = [captured_pub]() -> void {
        auto pub_ptr = captured_pub.lock();
        if (!pub_ptr) {
          return;
        }
        static int count = 0;
        msg_format::msg::ProcessMsg::UniquePtr msg(new msg_format::msg::ProcessMsg());
        if(count >= 4){
          count = 0;
        }
        else{
          count++;
        }
        msg->process = step.c_str();
        // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", step.c_str());
        printf(
          "Published message: %s, and address: 0x%" PRIXPTR "\n", msg->process.c_str(),
          reinterpret_cast<std::uintptr_t>(msg.get()));
        pub_ptr->publish(std::move(msg));
      };
    timer_ = this->create_wall_timer(0.1s, callback);
  }

  rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MainPublisher>());
    rclcpp::executors::SingleThreadedExecutor executor;

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("main_server");

    rclcpp::Service<msg_format::srv::ProcessService>::SharedPtr service =
    node->create_service<msg_format::srv::ProcessService>("process_service", &process);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start the process service");

//   rclcpp::spin(node);
    auto process = std::make_shared<MainPublisher>("main_process", "topic");
    executor.add_node(process);
    executor.add_node(node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
