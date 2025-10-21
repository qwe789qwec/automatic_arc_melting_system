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

    
    initializeSequences();
    // Initialize device state manager
    DeviceStateManager manager;
    manager.initializing = true;
    getDevicesListFromStep(sequence_[0][0]);
    for (const auto& device_id : devices_list_) {
        manager.addDevice(device_id);
    }
    manager.initializing = false;
    devices_manager_.push_back(manager);
    
    // moveToNextStep();
}

std::string ProcessController::updateDeviceStatuses(const std::string& command) {
    std::string message = "error";
    for (auto manager : devices_manager_) {
        if (manager.updateDeviceStatus(command)) {
            // return "update device status success";
            message = "success";
        }
    }
    return message;
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
    for (const auto& file_path : secquence_file_) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << file_path << std::endl;
            sequence_.push_back({
                "slider_init cobotta_init weighing_init plc_init",
                "slider_shelf_1 plc_buzz",
                "weighing_open slider_weight_pos cobotta_test",
                "slider_init cobotta_init weighing_init plc_init"
                "finished"
            });
            return;
        }
        else {
            std::cerr << "load process from file: " << file_path << std::endl;
            std::string line;
            std::vector<std::string> file_sequence;
            while (std::getline(file, line)) {
                // if line is empty or a comment, skip it
                if (line.empty() || line[0] == '#') {
                    continue;
                }
                file_sequence.push_back(line);
            }
            file.close();
            file_sequence.push_back("finished");
            sequence_.push_back(file_sequence);
        }
    }
}

void ProcessController::getDevicesListFromStep(const std::string& step) {
    devices_list_.clear();
    std::istringstream iss(step);
    std::string token;
    while (iss >> token) {
        size_t underscore_pos = token.find('_');
        if (underscore_pos != std::string::npos) {
            std::string device_id = token.substr(0, underscore_pos);
            if (std::find(devices_list_.begin(), devices_list_.end(), device_id) == devices_list_.end()) {
                devices_list_.push_back(device_id);
            }
        }
    }
}

std::string ProcessController::getCurrentStep() const {
    return current_step_;
}

bool ProcessController::isReadyToNextStep(int sequence_number) const {
    return devices_manager_[sequence_number].checkDevices(Situation::STANDBY);
}

bool ProcessController::isSequenceCompleted(int sequence_number) const {
    return step_index_[sequence_number] >= sequence_[sequence_number].size();
}

void ProcessController::moveToNextStep(int sequence_number) {
    if (step_index_[sequence_number] == 0 && current_step_ != "init") {
        updateDeviceStatuses(current_step_);
        return;
    }
    current_step_ = sequence_[sequence_number][step_index_[sequence_number]];
    updateDeviceStatuses(current_step_);
    step_index_[sequence_number]++;
}