#ifndef PROCESS_CONTROL_HPP
#define PROCESS_CONTROL_HPP

#include <string>
#include <vector>
#include "main_process/devices_state.hpp"

class ProcessController {
public:
    explicit ProcessController(std::string command = "init");
    std::string getCurrentStep() const;
    std::string updateDeviceStatuses(const std::string& command);
    bool isReadyToNextStep(int sequence_number) const;
    bool isSequenceCompleted(int sequence_number) const;
    void moveToNextStep(int sequence_number);
    
private:
    const std::vector<std::string> secquence_file_ = {"secquence/sequence_run.txt"};
    const int secquence_number_ = secquence_file_.size();

    // Device state manager
    std::vector<DeviceStateManager> devices_manager_;
    std::vector<std::string> devices_list_;

    
    // Current step and step index
    std::string current_step_;
    std::vector<size_t> step_index_;
    
    // Process sequences
    std::vector<std::vector<std::string>> sequence_;
    
    void getDevicesListFromStep(const std::string& step);
    void initializeSequences();
};

#endif // PROCESS_CONTROL_HPP