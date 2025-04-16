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
        /**
         * @brief Constructor
         * @param is_test_mode Whether to run the test sequence
         */
        explicit ProcessController(bool is_test_mode = true);
        
        /**
         * @brief Get the current process step
         * @return Current step string
         */
        std::string getCurrentStep() const;
        
        /**
         * @brief Process a device action update
         * @param action Device action string
         * @return Processing result
         */
        std::string processDeviceAction(const std::string& action);
        
        /**
         * @brief Check if all devices are in standby state
         * @return True if all devices are standby
         */
        bool areAllDevicesStandby() const;
        
        /**
         * @brief Extract device action at specified index from step string
         * @param step Current step string
         * @param index Device index
         * @return Device action, empty string if not found
         */
        std::string extractDeviceAction(const std::string& step, size_t index) const;
        
        /**
         * @brief Check if the sequence has been completed
         * @return True if sequence execution is finished
         */
        bool isSequenceCompleted() const;
        
        /**
         * @brief Check if running in test mode
         * @return True if in test mode
         */
        bool isTestMode() const;
        
        /**
         * @brief Move to the next step in the sequence
         * @return Description of next step result
         */
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
        
        /**
         * @brief Initialize the process sequences
         */
        void initializeProcessSequences();
        
        /**
         * @brief Get the currently active sequence
         * @return Reference to the current sequence
         */
        const std::vector<std::string>& getCurrentSequence() const;
};

#endif // PROCESS_CONTROL_HPP