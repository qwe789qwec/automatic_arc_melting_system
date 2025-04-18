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
    devices_.addDevice(Instrument::WEIGHING);
    devices_.addDevice(Instrument::COBOTTA);
    devices_.addDevice(Instrument::SLIDER);
    devices_.addDevice(Instrument::PLC);
    devices_.initialized = true;
    
    // Initialize process sequences
    initializeSequences();
    moveToNextStep();
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
            "slider init cobotta init weighing init plc init",
            "slider1 shelf1 plc buzz",
            "weighing open slider1 weight_pos cobotta test",
            "slider init cobotta init weighing init plc init",
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

std::string ProcessController::updateDeviceStatuses(const std::string& command) {    
    std::string update = "";
    for (const auto& device : devices_list_) {
        // match the device name in the command
        std::regex device_pattern("\\b" + device + "\\s+([^\\s]+(?:\\s+[^\\s]+)*)");
        std::smatch matches;
        
        // search for the device in the command
        if (std::regex_search(command, matches, device_pattern) && matches.size() > 1) {
            std::string action = matches[1].str();
            if (action == "standby") {
                devices_.updateDeviceStatus(device + " standby");
                update += device + " standby ";
            }
            else{
                devices_.updateDeviceStatus(device + " " + "action");
                update += device + " " + " action ";
            }
        }
    }

    if (update == "") {
        update = "No devices found in command";
    }

    return update;
}

bool ProcessController::isReadyToNextStep() const {
    return devices_.checkDevices(Situation::STANDBY);
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