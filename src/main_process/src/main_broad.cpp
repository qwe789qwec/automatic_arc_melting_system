#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process.hpp"
#include "msg_format/srv/process_format.hpp"
#include <memory>

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

std::string step = "init ";

void process(const std::shared_ptr<msg_format::srv::ProcessFormat::Request> request,
          std::shared_ptr<msg_format::srv::ProcessFormat::Response>      response)
{
  std::string action = request->action;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
  if(action.compare("one") == 0){
    response->result = "first ";
  }
  else if(action.compare("two") == 0){
    response->result = "second ";
  }
  else{
    response->result = "keep ";
  }
  step = response->result;
}

// class MainPublisher : public rclcpp::Node
// {
//   public:
//     MainPublisher()
//     : Node("main_process"), count_(0)
//     {
//       publisher_ = this->create_publisher<msg_format::msg::Process>("topic", 10);
//       timer_ = this->create_wall_timer(
//       500ms, std::bind(&MainPublisher::timer_callback, this));
//     }

//   private:
//     void timer_callback()
//     {
//       auto message = msg_format::msg::Process();
//       message.process = step.c_str() + std::to_string(count_++);
//       RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.process.c_str());
//       publisher_->publish(message);
//     }
//     rclcpp::TimerBase::SharedPtr timer_;
//     rclcpp::Publisher<msg_format::msg::Process>::SharedPtr publisher_;
//     size_t count_;
// };

struct MainPublisher : public rclcpp::Node
{
  MainPublisher(const std::string & name, const std::string & output)
  : Node(name, rclcpp::NodeOptions().use_intra_process_comms(true))
  {
    // Create a publisher on the output topic.
    pub_ = this->create_publisher<msg_format::msg::Process>(output, 10);
    std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;
    // Create a timer which publishes on the output topic at ~1Hz.
    auto callback = [captured_pub]() -> void {
        auto pub_ptr = captured_pub.lock();
        if (!pub_ptr) {
          return;
        }
        static int32_t count = 0;
        msg_format::msg::Process::UniquePtr msg(new msg_format::msg::Process());
        msg->process = step.c_str() + std::to_string(count++);
        // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.process.c_str());
        printf(
          "Published message: %s, and address: 0x%" PRIXPTR "\n", msg->process.c_str(),
          reinterpret_cast<std::uintptr_t>(msg.get()));
        pub_ptr->publish(std::move(msg));
      };
    timer_ = this->create_wall_timer(1s, callback);
  }

  rclcpp::Publisher<msg_format::msg::Process>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MainPublisher>());
    rclcpp::executors::SingleThreadedExecutor executor;

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("main_server");

    rclcpp::Service<msg_format::srv::ProcessFormat>::SharedPtr service =
    node->create_service<msg_format::srv::ProcessFormat>("process_format", &process);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

//   rclcpp::spin(node);
    auto process = std::make_shared<MainPublisher>("main_process", "topic");
    executor.add_node(process);
    executor.add_node(node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}