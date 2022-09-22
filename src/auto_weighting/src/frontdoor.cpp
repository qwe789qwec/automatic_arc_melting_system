#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/weighing_format.hpp"
#include "tcp_handle/tcp_socket.hpp"

#include <memory>

void plc_main(const std::shared_ptr<msg_format::srv::WeighingFormat::Request> request,
          std::shared_ptr<msg_format::srv::WeighingFormat::Response>      response)
{   
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());

    std::string plc_ip = "172.17.4.71";
    int plc_port = 35353;
    tcp_socket plc_handler(plc_ip, plc_port);
    plc_handler.create();
    plc_handler.write(action);
    char receive_msg[1024] = "init msg";
    plc_handler.receive(receive_msg);
    plc_handler.end();
    response->result = receive_msg;
    return;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("weighing_server");

    rclcpp::Service<msg_format::srv::WeighingFormat>::SharedPtr PlcServer =
        node->create_service<msg_format::srv::WeighingFormat>("weighing_format", &plc_main);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "plc_main");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
