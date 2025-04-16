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
    void updateDeviceStatus(const std::string& action);
    std::string extractDeviceAction(const std::string& step, size_t index) const;
    std::string processRequest(const std::string& action);
    bool areDevicesReady() const;
    
private:
    // Current process step
    std::string current_step_;
    
    // Step index in sequence
    size_t step_index_;
    
    // Test mode flag
    bool is_test_mode_;
    
    // Device state manager
    deviceState devices_;
    
    // Process sequences
    std::vector<std::string> production_sequence_;
    std::vector<std::string> test_sequence_;
    
    /**
     * @brief Initialize process sequences
     */
    void initializeSequences();
    
    /**
     * @brief Get the active sequence
     * @return Reference to current sequence
     */
    const std::vector<std::string>& getCurrentSequence() const;
};

#endif // PROCESS_CONTROL_HPP