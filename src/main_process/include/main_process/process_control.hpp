#ifndef PROCESS_CONTROL_HPP
#define PROCESS_CONTROL_HPP

#include <string>
#include <vector>
#include "main_process/devices_state.hpp"

/**
 * @brief Process controller class that manages process sequences and device states
 */
class ProcessController {
public:
    explicit ProcessController(bool is_test_mode = true);
    std::string getCurrentStep() const;
    std::string processDeviceAction(const std::string& action);
    bool areAllDevicesStandby() const;
    std::string extractDeviceAction(const std::string& step, size_t index) const;
    bool isSequenceCompleted() const;
    bool isTestMode() const;
    std::string moveToNextStep();
    
private:
    // Device state manager
    deviceState devices_;
    
    // Current step and step index
    std::string current_step_;
    size_t step_index_;
    
    // Test mode flag
    bool is_test_mode_;
    
    // Process sequences
    std::vector<std::string> production_sequence_;
    std::vector<std::string> test_sequence_;
    
    void initializeProcessSequences();
    const std::vector<std::string>& getCurrentSequence() const;
};

#endif // PROCESS_CONTROL_HPP