#include "main_process/process_control.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <unistd.h>
#include <limits.h>

ProcessController::ProcessController(std::string command)
    : current_step_(command), 
      step_index_(0){
    
    // Initialize device state manager
    devices_manager_.initializing = true;
    devices_manager_.addDevice("weighing");
    devices_manager_.addDevice("slider");
    devices_manager_.addDevice("cobotta");
    devices_manager_.addDevice("plc");
    devices_manager_.initializing = false;
    
    // Initialize process sequences
    initializeSequences();
    moveToNextStep();
}

std::string ProcessController::updateDeviceStatuses(const std::string& command) {
    bool message = devices_manager_.updateDeviceStatus(command);
    if (message) {
        return "update device status success";
    } else {
        return "update device status error";
    }
}

void ProcessController::initializeSequences() {

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cerr << "Current working directory: " << cwd << std::endl;
    } else {
        std::cerr << "Failed to get current directory" << std::endl;
    }
    
    // Load sequences from file or define them directly
    // try to load from file
    std::ifstream file(secquence_file_);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << secquence_file_ << std::endl;
        sequence_ = {
            "slider_init cobotta_init weighing_init plc_init",
            "slider_shelf1 plc_buzz",
            "weighing_open slider_weight_pos cobotta_test",
            "slider_init cobotta_init weighing_init plc_init",
            "finished"
        };
        return;
    }
    else {
        std::cerr << "load process from file: " << secquence_file_ << std::endl;
        std::string line;
        while (std::getline(file, line)) {
            // if line is empty or a comment, skip it
            if (line.empty() || line[0] == '#') {
                continue;
            }
            sequence_.push_back(line);
        }
        file.close();
        sequence_.push_back("finished");
    }
}

std::string ProcessController::getCurrentStep() const {
    return current_step_;
}

bool ProcessController::isReadyToNextStep() const {
    return devices_manager_.checkDevices(Situation::STANDBY);
}

bool ProcessController::isSequenceCompleted() const {
    return step_index_ >= sequence_.size();
}

void ProcessController::moveToNextStep() {
    if (step_index_ == 0 && current_step_ != "init") {
        updateDeviceStatuses(current_step_);
        return;
    }
    current_step_ = sequence_[step_index_];
    updateDeviceStatuses(current_step_);
    step_index_++;
}