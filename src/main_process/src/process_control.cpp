#include "main_process/process_control.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

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
}

void ProcessController::initializeSequences() {
    
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

std::string ProcessController::updateDeviceStatus(const std::string& status) {
    devices_.updateDeviceStatus(status);
    return "updated " + status;
}

bool ProcessController::isReadyToNextStep() const {
    return devices_.checkDevices(Situation::STANDBY);
}


bool ProcessController::isSequenceCompleted() const {
    return step_index_ >= sequence_.size();
}

void ProcessController::moveToNextStep() {
    if (step_index_ == 0 && current_step_ != "init") {
        return;
    }
    current_step_ = sequence_[step_index_];
    step_index_++;
}