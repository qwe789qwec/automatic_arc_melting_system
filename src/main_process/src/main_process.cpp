#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "devices_state.hpp"
#include "sequence.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

std::string step = "init";

void process(const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
             std::shared_ptr<msg_format::srv::ProcessService::Response> response)
{
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
    state Devices;
    Devices.addDevice("slider");
    Devices.addDevice("weighing");
    Devices.addDevice("cobotta");
    Devices.updateDeviceStatus(action);

    Sequence seq;
    seq.process();     // 输出 "State A"
    seq.setState(new weighing());
    seq.process();     // 输出 "State B"
    seq.setState(new outWeighingSample());
    seq.process();     // 输出 "State C"

    if (step.compare("init") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 4";
            Devices.updateDeviceStatus("slider action");
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 1") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 2";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 2") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 3";
            Devices.updateDeviceStatus("slider action");
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 3") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 4";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 4") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 5";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 5") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 6";
            Devices.updateDeviceStatus("slider action");
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 6") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 7";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 7") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 8";
            Devices.updateDeviceStatus("slider action");
        }
    }
    else if (step.compare("step 8") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 9";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 9") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 10";
            Devices.updateDeviceStatus("slider action");
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 10") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 11";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 11") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 12";
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 12") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 13";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 13") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 14";
            Devices.updateDeviceStatus("slider action");
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 14") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 15";
            Devices.updateDeviceStatus("cobotta action");
        }
    }
    else if (step.compare("step 15") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 16";
            Devices.updateDeviceStatus("weighing action");
        }
    }
    else if (step.compare("step 16") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "step 17";
        }
    }
    else if (step.compare("step 17") == 0)
    {
        if (Devices.checkDevices())
        {
            response->result = "OK";
            step = "Standby";
        }
    }
    else
    {
        response->result = action;
        response->result = "OK";
        // step = "init";
    }
    response->result = "OK";
}

struct MainPublisher : public rclcpp::Node
{
    MainPublisher(const std::string &name, const std::string &output)
        : Node(name, rclcpp::NodeOptions().use_intra_process_comms(true))
    {
        // Create a publisher on the output topic.
        pub_ = this->create_publisher<msg_format::msg::ProcessMsg>(output, 10);
        std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;
        // Create a timer which publishes on the output topic at ~1Hz.
        auto callback = [captured_pub]() -> void
        {
            auto pub_ptr = captured_pub.lock();
            if (!pub_ptr)
            {
                return;
            }
            static int count = 0;
            msg_format::msg::ProcessMsg::UniquePtr msg(new msg_format::msg::ProcessMsg());
            if (count >= 4)
            {
                count = 0;
            }
            else
            {
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

int main(int argc, char *argv[])
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
