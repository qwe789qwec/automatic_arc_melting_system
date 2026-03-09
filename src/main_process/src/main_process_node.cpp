#include "main_process/main_process_node.hpp"
#include <sstream>

using namespace std::chrono_literals;

static std::string trim_copy(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

std::string MainProcessNode::get_kv(const std::string& action, const std::string& key) {
    // actionの中から "KEY=VALUE" 形式をスペース区切りで探索
    std::istringstream iss(action);
    std::string token;
    while (iss >> token) {
        auto pos = token.find('=');
        if (pos != std::string::npos) {
            auto k = token.substr(0, pos);
            if (k == key) {
                return token.substr(pos + 1);
            }
        }
    }
    return "";
}


MainProcessNode::MainProcessNode(const std::string& node_name, std::string command)
    : Node(node_name), 
    process_controller_(command), 
    last_published_step_(""),
    current_task_id_("") {
    
    // Create service
    process_service_ = create_service<msg_format::srv::ProcessService>(
        "process_service",
        std::bind(&MainProcessNode::processServiceCallback, this, 
                  std::placeholders::_1, std::placeholders::_2));
                  
    // Create publisher for current step
    step_publisher_ = create_publisher<msg_format::msg::ProcessMsg>("topic", 10);

    // Publisher for task status (CSV workflow)
    task_status_publisher_ = create_publisher<msg_format::msg::ProcessMsg>("task_status", 10);
    
    // Setup timer to periodically publish current step
    publish_timer_ = create_wall_timer(2.0s, 
        std::bind(&MainProcessNode::publishCurrentStep, this));
        
    RCLCPP_INFO(get_logger(), "Main process node initialized");
    RCLCPP_INFO(get_logger(), "Starting with step: %s", process_controller_.getCurrentStep().c_str());
}

void MainProcessNode::processServiceCallback(
    const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
    std::shared_ptr<msg_format::srv::ProcessService::Response> response) {
    
    const std::string action = request->action;
    RCLCPP_INFO(get_logger(), "Service request received: %s", action.c_str());

    // Load sequence file
    const auto seq_path = get_kv(action, "LOADSEQ_FILE");
    const auto task_id = get_kv(action, "TASK_ID");

    if (!seq_path.empty()) {
        bool ok = process_controller_.loadSequenceFromFile(seq_path);
        if (ok) {
            current_task_id_ = task_id;
            response->result = std::string("loaded: ") + seq_path;
            RCLCPP_INFO(get_logger(), "Loaded sequence file: %s (task_id=%s)", seq_path.c_str(), task_id.c_str());
        } else {
            response->result = std::string("failed to load: ") + seq_path;
            RCLCPP_ERROR(get_logger(), "Failed to load sequence file: %s", seq_path.c_str());
        }
        return;
        }
    

    // Update device status
    std::string message = process_controller_.updateDeviceStatuses(action);
    response->result = message;
    RCLCPP_INFO(get_logger(), "Device status updated: %s", message.c_str());
}

void MainProcessNode::publishCurrentStep() {
    
    // Get current step
    // if (process_controller_.isSequenceCompleted() && process_controller_.isReadyToNextStep()) {
    //     RCLCPP_INFO(get_logger(), "Process sequence completed");
    // }

    // シーケンス完了チェック
    if (process_controller_.isSequenceCompleted()) {
        if (!current_task_id_.empty()) {
            // タスク完了を通知
            msg_format::msg::ProcessMsg status_msg;
            status_msg.process = std::string("TASK_COMPLETED=") + current_task_id_;
            task_status_publisher_->publish(status_msg);
            RCLCPP_INFO(get_logger(), "Published task completion: %s", 
                        status_msg.process.c_str());
            current_task_id_.clear();
        }
        return;  // 完了後は次のロード指示を待つ
    }
    
    
    
    if (process_controller_.isReadyToNextStep()) {
        process_controller_.moveToNextStep();
    }
    std::string current_step = process_controller_.getCurrentStep();
    
    // Only log when step changes to reduce message volume
    if (current_step != last_published_step_) {
        RCLCPP_INFO(get_logger(), "Publishing step: %s", current_step.c_str());
        last_published_step_ = current_step;
    }
    
    // Publish current step
    msg_format::msg::ProcessMsg msg;
    msg.process = current_step;
    step_publisher_->publish(msg);
}