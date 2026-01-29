#include "main_process/process_control.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
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

void ProcessController::readSegmentFile(std::string file_name) {
    std::ifstream file(file_name);
    std::string line;
    // do not use A file in B file and B file in A file to avoid infinite loop
    if (!file.is_open()) {
        std::cerr << "\033[1;31m[ERROR] Could not open: " << file_name << "\033[0m" << std::endl;
        std::exit(EXIT_FAILURE); 
    }
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        sequence_.push_back(line);
        if (line.compare(0, 8, "SEGMENT_") == 0) {
            std::string file_name = line.substr(8);
            readSegmentFile(file_name);
        }
    }
    file.close();
}

void ProcessController::initializeSequences() {

    // Check Current Working Directory for debugging
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cerr << "[INFO] Working Directory: " << cwd << std::endl;
    }

    std::cerr << "[INFO] Loading sequence file: " << sequence_file_ << std::endl;
    std::ifstream file(sequence_file_);
    
    // Error: Cannot open main sequence file
    if (!file.is_open()) {
        std::cerr << "\033[1;31m[ERROR] Could not open: " << sequence_file_ << "\033[0m" << std::endl;
        std::exit(EXIT_FAILURE); 
    }
    else {
        std::cerr << "load process from file: " << sequence_file_ << std::endl;
        std::string line;
        size_t count_step = 0;
        while (std::getline(file, line)) {
            // if line is empty or a comment, skip it
            if (line.empty() || line[0] == '#') {
                continue;
            }
            if (line.compare(0, 8, "SEGMENT_") == 0) {
                // Note: readSegmentFile should also use std::exit on failure
                std::string file_name = line.substr(8);
                readSegmentFile(file_name); 
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