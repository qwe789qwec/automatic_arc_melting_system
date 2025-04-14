#include <chrono>
#include <cstdlib>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "slider_control/slider.hpp"
#include "slider_control/slider_node.hpp"

std::string slider_ip = "192.168.0.3";
int slider_port = 64511;

int main(int argc, char *argv[])
{
    // 初始化ROS2
    rclcpp::init(argc, argv);
    
    // 建立滑塊控制對象
    slider slider_controller(slider_ip, slider_port);
    
    // 測試功能
    bool test = false;
    if (argc == 2 && test == true)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start test");
    }
    
    if (test){
        test = false;
        std::string test_action = "slider " + std::string(argv[1]);
        printf("test action: %s\n", test_action.c_str());
        slider_controller.make_action(test_action);
    }

    // 建立並執行節點
    auto node = std::make_shared<SliderNode>(slider_controller);
    rclcpp::spin(node);
    
    // 關閉ROS2
    rclcpp::shutdown();
    return 0;
}