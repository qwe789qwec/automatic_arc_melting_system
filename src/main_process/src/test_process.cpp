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

std::string step = "init";
bool enter_pressed = false;

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

    const int stepSize = 19;
    std::vector<std::string> stepArray(stepSize);
    stepArray[0] = "init";
    stepArray[1] = "weighing 6.7 slider1 Pos4";
    stepArray[2] = "cobotta TakeWeightDose";
    stepArray[3] = "weighing Close slider1 Pos2";
    stepArray[4] = "cobotta PutStoreDose";
    stepArray[5] = "slider1 Pos3";
    stepArray[6] = "cobotta TakeStoreDose";
    stepArray[7] = "weighing Open slider1 Pos4";
    stepArray[8] = "cobotta PutWeightDose";
    stepArray[9] = "weighing 8.8";
    stepArray[10] = "cobotta TakeWeightHolder";
    stepArray[11] = "weighing Close slider1 Pos1";
    stepArray[12] = "cobotta PutStandbyHolder";
    stepArray[13] = "slider PutChamberHolder";
    stepArray[14] = "PLC CloseChamber";
    stepArray[15] = "PLC Pump";
    stepArray[16] = "PLC arc Slider arc";
    stepArray[17] = "PLC Vent";
    stepArray[18] = "PLC OpenChamber";

    const int testSize = 6;
    std::vector<std::string> testArray(testSize);
    testArray[0] = "init";
    testArray[1] = "slider1 pos2";
    testArray[2] = "slider1 pos3";
    testArray[3] = "slider1 pos4";
    testArray[4] = "slider1 pos5";
    testArray[5] = "standby";

    static deviceState Devices;
    Devices.addDevice(Devices::SLIDER);
    Devices.initialized = true;
    Devices.addDevice(Devices::WEIGHING);
    Devices.addDevice(Devices::COBOTTA);
    Devices.addDevice(Devices::PLC);
    Devices.updateDeviceStatus(action);

    if (Devices.checkDevices(DeviceStatus::STANDBY))
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Press Enter to continue...");
    }

    if (enter_pressed && Devices.checkDevices(DeviceStatus::STANDBY))
    {
        for (int i = 0; i < testSize; i++)
        {
            if (step.compare(testArray[i]) == 0)
            {
                if ((i + 1) < testSize)
                {
                    step = testArray[i + 1];
                }
                response->result = "OK";
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step here: %s", step.c_str());
                Devices.updateDeviceStatus(checkProcess(step, 0));
                Devices.updateDeviceStatus(checkProcess(step, 1));
                Devices.updateDeviceStatus(checkProcess(step, 2));
                enter_pressed = false;
                break;
            }
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
        timer_ = this->create_wall_timer(0.5s, callback);
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

    auto keyinput = std::make_shared<KeyPublisher>();
    executor.add_node(keyinput);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
