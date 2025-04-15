#include <cstdlib>
#include "weighing_control/weighing_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // 处理测试参数
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        WeighingSystem::test_weighing_machine(argv[1]);
        test = false;
    }
    
    // 创建并运行节点
    auto node = std::make_shared<WeighingSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}