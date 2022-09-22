#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/weighing_format.hpp"
#include "tcp_handle/tcp_socket.hpp"

#include <memory>

void plc_main(const std::shared_ptr<msg_format::srv::WeighingFormat::Request> request,
          std::shared_ptr<msg_format::srv::WeighingFormat::Response>      response)
{   
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());

    std::string weighing_ip = "192.168.0.2";
    // std::string weighing_ip = "172.17.4.71";
    int weighing_port = 8001;
    // int weighing_port = 35353;
    tcp_socket weiging_handler(weighing_ip, weighing_port);
    weiging_handler.create();
    if(action.compare("open\r\n")){
        weiging_handler.write("QRA 60 7 2\r\n");
        // weiging_handler.write("123\r\n");
    }
    else if(action.compare("close\r\n")){
        weiging_handler.write("QRA 60 7 3\r\n");
        // weiging_handler.write("test\r\n");
    }
    char receive_msg[1024] = "init msg";
    weiging_handler.receive(receive_msg);
    weiging_handler.end();
    response->result = receive_msg;
    return;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("weighing_format");

    rclcpp::Service<msg_format::srv::WeighingFormat>::SharedPtr WeighingServer =
        node->create_service<msg_format::srv::WeighingFormat>("weighing_format", &plc_main);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "plc_main");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
