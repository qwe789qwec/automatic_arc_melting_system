#ifndef PROCESS_CONTROL_HPP
#define PROCESS_CONTROL_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "main_process/devices_state.hpp"

class ProcessController {
public:
    explicit ProcessController(std::string command = "init");
    std::string getCurrentStep() const;
    std::string updateDeviceStatuses(const std::string& command);
    bool isReadyToNextStep() const;
    bool isSequenceCompleted() const;
    void moveToNextStep();

private:
    const std::string sequence_file_ = "sequence/sequence.txt";

    // Device state manager
    DeviceStateManager devices_manager_;
    std::vector<std::string> devices_list_ = {"weighing", "slider", "plc", "cobotta", "record"};

    // Current step and step index
    std::string current_step_;
    size_t step_index_;
    std::unordered_map<std::string, size_t> label_map_;
    std::unordered_map<std::string, size_t> vars_map_;
    
    // Process sequences
    std::vector<std::string> sequence_;

    void initializeSequences();
};

#endif // PROCESS_CONTROL_HPP
