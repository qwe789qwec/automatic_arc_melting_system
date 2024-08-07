#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
// #include "main_process/sequence.hpp"
#include "main_process/devices_state.hpp"
#include "std_msgs/msg/string.hpp"

#define TTY_PATH "/dev/tty"
#define STTY_US "stty raw -echo -F "
#define STTY_DEF "stty -raw echo -F "

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

std::string step = "slider init cobotta init weighing init plc init";
bool enter_pressed = true;

std::string checkProcess(std::string currentstep, size_t index)
{
    std::vector<std::string> devices = {"weighing", "slider", "slider1", "plc", "cobotta"};

    size_t foundIndex = 0;
    for (std::string device : devices)
    {
        size_t found = currentstep.find(device);
        if (found != std::string::npos)
        {
            if (foundIndex == index)
            {
                return device + " action";
            }
            foundIndex++;
        }
    }

    return "Keyword not found at index " + std::to_string(index);
}

void process(const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
             std::shared_ptr<msg_format::srv::ProcessService::Response> response)
{
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
    // Sequence sequence;
    // sequence.devices.updateDeviceStatus(action);

    // Nb3Al Nb = 455.8 Al = 44.2

    const std::vector<std::string> stepArray = {
        "slider init cobotta init weighing init plc init",
        "slider1 cup_stock_r",
        "cobotta cupstock_take_bowl_5",
        "weighing open slider1 weight_pos",
        "cobotta weight_put_bowl",
        "slider1 shelf1 weighing close",
        "cobotta shelf_take_dose",
        "weighing open slider1 weight_pos",
        "cobotta weight_put_dose",
        "weighing mgram44.2",
        "cobotta weight_take_dose",
        "weighing close slider1 shelf1",
        "cobotta shelf_put_dose",
        "slider1 shelf3",
        "cobotta shelf_take_dose_2",
        "weighing open slider1 weight_pos",
        "cobotta weight_put_dose",
        "weighing mgram455.8",
        "cobotta weight_take_bowl",
        "weighing close slider1 pos1",
        "cobotta put_bowl_intoarc_20230727 plc gateOpen",
        "slider weight_pos weighing open",
        "slider put_cup_arc cobotta weight_take_dose",
        "plc gateClose slider1 shelf3 weighing close",
        "plc pump cobotta shelf_put_dose_2",
        "slider arcinit",

        "plc buzz",
        "plc arcOn",
        "slider arc_cw",
        "plc arcOff",
        "plc autoFlip",

        "plc buzz",
        "plc arcOn",
        "slider arc_ccw",
        "plc arcOff",
        "plc autoFlip",

        "plc buzz",
        "plc arcOn",
        "slider arc_cw",
        "plc arcOff",
        "plc autoFlip",

        "plc buzz",
        "plc arcOn",
        "slider arc_ccw",
        "plc arcOff",        

        "plc vent slider pos1",
        "plc gateOpen",
        "slider take_cup_arc",
        "plc gateClose cobotta intoarc_take_bowl_20230727",
        "slider1 product_stock_r",
        "cobotta product_put_bowl",
        "slider1 pos1"
    };

    const std::vector<std::string> testArray = {
        "slider init cobotta init weighing init plc init",
        "plc gateOpen",
        "plc buzz",
    };

    const std::vector<std::string>* processArray = nullptr;
    bool useStepArray = false;

    if (useStepArray) {
        processArray = &stepArray;
    } else {
        processArray = &testArray;
    }

    static deviceState Devices;
    Devices.addDevice(Devices::WEIGHING);
    Devices.addDevice(Devices::COBOTTA);
    Devices.addDevice(Devices::SLIDER);
    Devices.addDevice(Devices::PLC);
    Devices.initialized = true;
    Devices.updateDeviceStatus(action);

    static long unsigned int stepNumber = 0;

    if (Devices.checkDevices(DeviceStatus::STANDBY))
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Press Enter to continue...");
    }

    // if (enter_pressed && Devices.checkDevices(DeviceStatus::STANDBY))
    if (Devices.checkDevices(DeviceStatus::STANDBY))
    {
        if (step.compare((*processArray)[stepNumber]) == 0)
        {
            stepNumber++;
            if (stepNumber < processArray->size())
            {
                step = (*processArray)[stepNumber];
                response->result = "OK";
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step here: %s", step.c_str());
                Devices.updateDeviceStatus(checkProcess(step, 0));
                Devices.updateDeviceStatus(checkProcess(step, 1));
                Devices.updateDeviceStatus(checkProcess(step, 2));
                enter_pressed = false;
            }
            else
            {
                // 处理完最后一个步骤后，重置或处理结束
                step = "finished";
                response->result = "Finished";
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "All steps completed.");
            }
        }
        else
        {
            response->result = "Error";
            step = "Error";
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Invalid step: %s", step.c_str());
        }
    }
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
        timer_ = this->create_wall_timer(1s, callback);
    }

    rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

class KeyPublisher : public rclcpp::Node
{
public:
    KeyPublisher()
        : Node("key_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&KeyPublisher::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        //check if the enter key is pressed
        if (getchar() == '\n')
        {
            enter_pressed = true;
        }
        message.data = "Key press time: " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());

        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
    rclcpp::executors::SingleThreadedExecutor executor;

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("main_server");

    rclcpp::Service<msg_format::srv::ProcessService>::SharedPtr service =
        node->create_service<msg_format::srv::ProcessService>("process_service", &process);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start the process service");
    executor.add_node(node);

    auto process = std::make_shared<MainPublisher>("main_process", "topic");
    executor.add_node(process);

    // auto keyinput = std::make_shared<KeyPublisher>();
    // executor.add_node(keyinput);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
