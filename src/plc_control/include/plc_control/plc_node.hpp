#ifndef PLC_NODE_H
#define PLC_NODE_H

#include <chrono>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "plc_control/plc.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class PlcSystem : public rclcpp::Node
{
    public:
        PlcSystem();
        ~PlcSystem() = default;

        // 测试功能的公共方法
        static bool test_plc_action(const std::string& action_param);
        
        // Modbus功能
        static char* modbus(const char* function, const char* component, const char* data);
        static void printchar(const char* message, int size);

    private:
        // 参数
        std::string plc_ip_;
        int plc_port_;
        std::string current_step_;
        
        // 组件
        std::unique_ptr<plc> plc_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // 回调和服务方法
        void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
        bool call_process_service(const std::string& action);
};

#endif // PLC_NODE_H