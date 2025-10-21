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

ProcessController::ProcessController(){
    for (size_t i = 0; i < sequence_files_.size(); ++i) {
        const auto& file_path = sequence_files_[i];
        std::ifstream file(file_path);
        Process seq;
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << file_path << std::endl;
            seq.sequence = {
                "start",
                "slider_init cobotta_init weighing_init plc_init",
                "slider_shelf_1 plc_buzz",
                "weighing_open slider_weight_pos cobotta_test",
                "slider_init cobotta_init weighing_init plc_init",
                "finished"
            };
        } else {
            std::string line;
            seq.sequence.push_back("start");
            while (std::getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;
                seq.sequence.push_back(line);
            }
            seq.sequence.push_back("finished");
        }

        seq.device_manager.initializing = true;
        std::vector<std::string> devices = getDevicesListFromStep(seq.sequence[1]);
        for (const auto& device : devices)
            seq.device_manager.addDevice(device);
        seq.device_manager.initializing = false;

        sequences_[i] = std::move(seq);
    }

    moveToNextStep(0);
}

std::string ProcessController::updateDeviceStatuses(const std::string& command) {
    bool success = false;

    for (auto& item : sequences_) {
        // item = pair<key, value>
        auto& process = item.second;
        if (process.device_manager.updateDeviceStatus(command)) {
            success = true;
        }
    }

    return success ? "success" : "error";
}

std::vector<std::string> ProcessController::getDevicesListFromStep(const std::string& step) {
    std::vector<std::string> devices_list_;
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
    return devices_list_;
}

std::string ProcessController::getCurrentStep() {
    std::string current_step_ = "";

    for (auto& item : sequences_) {
        // item = pair<key, value>
        auto& process = item.second;
        if (process.current_step >= process.sequence.size()) {
            continue;
        }

        const std::string& step = process.sequence[process.current_step];
        if (step == "finished" || step == "start") {
            continue;
        }

        current_step_ += step + " ";
    }

    return current_step_;
}

int ProcessController::getCurrentStepNumber(int process_number) const {
    return sequences_.at(process_number).current_step;
}

bool ProcessController::isReadyToNextStep(int process_number) const {
    auto seq = sequences_.find(process_number);
    if (seq != sequences_.end()) {
        return seq->second.device_manager.checkDevices(Situation::STANDBY);
    }
    return false;
}

bool ProcessController::isSequenceCompleted(int process_number) const {
    const auto& seq = sequences_.at(process_number);
    return seq.current_step >= seq.sequence.size();
}

void ProcessController::moveToNextStep(int process_number) {
    sequences_.at(process_number).current_step++;
}

void ProcessController::insertSequence(int process_number, std::vector<std::string> seq) {
    sequences_.at(process_number).sequence.insert(
        sequences_.at(process_number).sequence.begin() + sequences_.at(process_number).current_step + 1,
        seq.begin(),
        seq.end()
    );
}