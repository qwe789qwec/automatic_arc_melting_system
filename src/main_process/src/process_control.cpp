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

    if (command.compare(0, 4, "VAR_") == 0) {
        handleVariable(command);
    }

    if (message) {
        return "update device status success";
    } else {
        return "update device status error";
    }
}

bool ProcessController::handleConditionals(const std::string& command) {
    bool is_if = command.compare(0, 3, "IF_") == 0;
    bool is_ifnot = command.compare(0, 6, "IFNOT_") == 0;

    if (!is_if && !is_ifnot) return false;

    // 1. Extract the raw condition string
    std::string condition = is_if ? command.substr(3) : command.substr(6);

    // 2. Updated Regex: Group 3 is now (\w+) to support both digits and variable names
    std::regex condition_regex(R"((\w+)(==|!=|>=|<=|>|<)(\w+))");
    std::smatch match;

    if (std::regex_search(condition, match, condition_regex)) {
        std::string left_var = match[1];
        std::string op = match[2];
        std::string right_side = match[3];

        // 3. Get values for comparison
        int left_val = vars_map_.count(left_var) ? vars_map_[left_var] : 0;
        int right_val;

        // Check if right_side is a variable name in the map
        if (vars_map_.count(right_side)) {
            right_val = vars_map_[right_side];
        } else {
            // If not in map, try to treat it as a literal number
            try {
                right_val = std::stoi(right_side);
            } catch (...) {
                right_val = 0; // Or handle as an error
            }
        }

        // 4. Perform comparison
        bool result = false;
        if (op == "==")      result = (left_val == right_val);
        else if (op == "!=") result = (left_val != right_val);
        else if (op == ">=") result = (left_val >= right_val);
        else if (op == "<=") result = (left_val <= right_val);
        else if (op == ">")  result = (left_val > right_val);
        else if (op == "<")  result = (left_val < right_val);

        // 5. Invert if it's an IFNOT
        return is_if ? result : !result;
    }

    return false;
}

void ProcessController::handleVariable(const std::string& command) {
    if (command.compare(0, 4, "VAR_") != 0) return;

    std::regex var_regex(R"(VAR_(\w+)\s*(=|\+=|-=)\s*(\w+))");
    std::smatch match;

    if (std::regex_search(command, match, var_regex)) {
        std::string left_var = match[1];
        std::string op = match[2];
        std::string right_side = match[3];

        // 2. Resolve the right-side value
        int right_val = 0;
        if (vars_map_.count(right_side)) {
            right_val = vars_map_[right_side];
        } else {
            try {
                right_val = std::stoi(right_side);
            } catch (...) {
                printf("[ERROR] Variable operation aborted.\n");
                return; 
            }
        }

        // 3. Apply the operator
        // If the left variable doesn't exist yet, it defaults to 0 in map
        if (op == "=") {
            vars_map_[left_var] = right_val;
        } else if (op == "+=" && running_) {
            vars_map_[left_var] += right_val;
        } else if (op == "-=" && running_) {
            vars_map_[left_var] -= right_val;
        }

        printf("[VAR] %s is now %d\n", left_var.c_str(), vars_map_[left_var]);
    } else {
        printf("[ERROR] Variable operation aborted.\n");
    }
}

void ProcessController::readSegmentFile(std::string file_name) {
    std::string file_path = "segment/" + file_name;
    std::ifstream file(file_path);
    std::string line;
    // do not use A file in B file and B file in A file to avoid infinite loop
    if (!file.is_open()) {
        std::cerr << "\033[1;31m[ERROR] Could not open: " << file_path << "\033[0m" << std::endl;
        std::exit(EXIT_FAILURE); 
    }
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        if (line.compare(0, 8, "SEGMENT_") == 0) {
            std::string file_name = line.substr(8);
            readSegmentFile(file_name);
        }
        sequence_.push_back(line);
        if (!isCommandValid(line)) {
            std::cerr << "\033[1;31m[ERROR] Invalid command found in script: " << line << "\033[0m" << std::endl;
            std::cerr << "[HELP] Command must contain a valid device name or a control prefix." << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    file.close();
}

bool ProcessController::isCommandValid(const std::string& command) const
{
    // 1. check device keywords
    for (const auto& device : devices_list_) {
        if (command.find(device) != std::string::npos) {
            return true;
        }
    }

    // 2. check prefixes
    for (const auto& prefix : prefixes_) {
        if (command.rfind(prefix, 0) == 0) {  // starts with prefix
            return true;
        }
    }

    // 3. invalid command
    std::cerr << "\033[1;31m[ERROR] Invalid command detected: "
              << command << "\033[0m" << std::endl;
    return false;
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

            if (!isCommandValid(line)) {
                std::cerr << "\033[1;31m[ERROR] Invalid command found in script: " << line << "\033[0m" << std::endl;
                std::cerr << "[HELP] Command must contain a valid device name or a control prefix." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            
            sequence_.push_back(line);
        }
        file.close();
        sequence_.push_back("finished");
    }

    // generate label map
    for (size_t i = 0; i < sequence_.size(); i++) {
        if (sequence_[i].compare(0, 6, "LABEL_") == 0) {
            std::string label_name = sequence_[i].substr(6);
            
            // Safety check: Avoid duplicate labels
            if (label_map_.find(label_name) != label_map_.end()) {
                std::cerr << "[ERROR] Duplicate label detected: " << label_name << std::endl;
                std::exit(EXIT_FAILURE);
            }
            
            // Map the label to this index.
            label_map_[label_name] = i;
        }
        else if (sequence_[i].compare(0, 4, "VAR_") == 0) {\
            handleVariable(sequence_[i]);
        }
    }

    running_ = true;
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

    // Skip non-executable commands
    while (step_index_ < sequence_.size()) {
        std::string cmd_no_space = sequence_[step_index_];
        cmd_no_space.erase(std::remove_if(cmd_no_space.begin(), cmd_no_space.end(), ::isspace), cmd_no_space.end());
        
        if (cmd_no_space.find("VAR_") == 0) {
            handleVariable(cmd_no_space);
        } else if (cmd_no_space.find("GOTO_") == 0) {
            step_index_ = label_map_[cmd_no_space.substr(5)];
            continue; // Skip the increment at the end
        } else if (cmd_no_space.find("IF_") == 0 || cmd_no_space.find("IFNOT_") == 0) {
            if (!handleConditionals(cmd_no_space)) {
                step_index_ += 2; // Skip next command if condition fails
                continue;
            }
        } else if (cmd_no_space.find("LABEL_") == 0) {
            // Just skip labels
        } else {
            break; // Found a regular command, exit loop
        }
        step_index_++;
    }

    current_step_ = sequence_[step_index_];
    updateDeviceStatuses(current_step_);
    step_index_++;
}