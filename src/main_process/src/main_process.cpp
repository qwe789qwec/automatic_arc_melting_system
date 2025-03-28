#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
// #include "main_process/sequence.hpp"
#include "main_process/devices_state.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

std::string step = "slider init cobotta init weighing init plc init";
bool enter_pressed = true;
std::vector<std::string> stepArray;  // 動的な配列に変更

bool loadStepsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Could not open file: %s", filename.c_str());
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Trim trailing commas or spaces
        if (!line.empty()) {
            // Remove trailing comma if exists
            if (line.back() == ',') {
                line.pop_back();
            }
            stepArray.push_back(line);
        }
    }

    file.close();
    return true;
}

std::string checkProcess(std::string currentstep, size_t index) {
    std::vector<std::string> devices = {"weighing", "slider", "slider1", "plc", "cobotta"};
    
    size_t foundIndex = 0;
    for (std::string device : devices) {
        size_t found = currentstep.find(device);
        if (found != std::string::npos) {
            if (foundIndex == index) {
                return device + " action";
            }
            foundIndex++;
        }
    }

    return "Keyword not found at index " + std::to_string(index);
}

void process(const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
             std::shared_ptr<msg_format::srv::ProcessService::Response> response) {
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
    // Sequence sequence;
    // sequence.devices.updateDeviceStatus(action);

    // Nb3Al Nb = 455.8 Al = 44.2

    static deviceState Devices;
    Devices.addDevice(Instrument::WEIGHING);
    Devices.addDevice(Instrument::COBOTTA);
    Devices.addDevice(Instrument::SLIDER);
    Devices.addDevice(Instrument::PLC);
    Devices.initialized = true;
    Devices.updateDeviceStatus(action);

    static long unsigned int stepNumber = 0;

    if (Devices.checkDevices(Situation::STANDBY)) {
        if (step.compare(stepArray[stepNumber]) == 0) {
            stepNumber++;
            if (stepNumber < stepArray.size()) {
                step = stepArray[stepNumber];
                response->result = "OK";
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "step here: %s", step.c_str());
                Devices.updateDeviceStatus(checkProcess(step, 0));
                Devices.updateDeviceStatus(checkProcess(step, 1));
                Devices.updateDeviceStatus(checkProcess(step, 2));
                enter_pressed = false;
            } else {
                step = "finished";
                response->result = "Finished";
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "All steps completed.");
            }
        } else {
            response->result = "Error";
            step = "Error";
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Invalid step: %s", step.c_str());
        }
    }
}

struct MainPublisher : public rclcpp::Node {
    MainPublisher(const std::string &name, const std::string &output)
        : Node(name, rclcpp::NodeOptions().use_intra_process_comms(true)) {
        pub_ = this->create_publisher<msg_format::msg::ProcessMsg>(output, 10);
        std::weak_ptr<std::remove_pointer<decltype(pub_.get())>::type> captured_pub = pub_;
        auto callback = [captured_pub]() -> void {
            auto pub_ptr = captured_pub.lock();
            if (!pub_ptr) {
                return;
            }
            static int count = 0;
            msg_format::msg::ProcessMsg::UniquePtr msg(new msg_format::msg::ProcessMsg());
            if (count >= 4) {
                count = 0;
            } else {
                count++;
            }
            msg->process = step.c_str();
            printf("Published message: %s, and address: 0x%" PRIXPTR "\n", msg->process.c_str(),
                   reinterpret_cast<std::uintptr_t>(msg.get()));
            pub_ptr->publish(std::move(msg));
        };
        timer_ = this->create_wall_timer(1s, callback);
    }

    rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

class KeyPublisher : public rclcpp::Node {
public:
    KeyPublisher()
        : Node("key_publisher"), count_(0) {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&KeyPublisher::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        if (getchar() == '\n') {
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

int main(int argc, char *argv[]) {
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

    // ファイルからstepArrayを読み込む
    if (!loadStepsFromFile("/home/song/Documents/ww/automatic_arc_melting_system/src/main_process/src/steps.txt")) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to load steps from file.");
        return 1;  // エラー終了
    }

    executor.spin();

    rclcpp::shutdown();
    return 0;
}
