#include "main_process/process_control.hpp"

ProcessController::ProcessController(bool is_test_mode)
    : current_step_("slider init cobotta init weighing init plc init"),
      step_index_(0),
      is_test_mode_(is_test_mode) {
    
    // Initialize devices
    devices_.addDevice(Instrument::WEIGHING);
    devices_.addDevice(Instrument::COBOTTA);
    devices_.addDevice(Instrument::SLIDER);
    devices_.addDevice(Instrument::PLC);
    devices_.initialized = true;
    
    // Initialize process sequences
    initializeSequences();
}

void ProcessController::initializeSequences() {
    // Production sequence with all manufacturing steps
    production_sequence_ = {
        "slider init cobotta init weighing init plc init",
        "cobotta take_cup_from_stock",
        "weighing open slider1 weight_pos",
        "cobotta put_cup_to_weight",
        "slider1 shelf1 weighing close",
        "cobotta take_dose_from_shelf",
        "weighing open slider1 weight_pos",
        "cobotta put_dose_to_weight",
        "weighing mgram180.2",
        "cobotta take_dose_from_weight",
        "weighing close slider1 shelf1",
        "cobotta put_dose_to_shelf",
        "slider1 shelf3",
        "cobotta take_dose_from_shelf2",
        "weighing open slider weight_pos",
        "cobotta put_dose_to_weight",
        "weighing mgram319.8",
        "cobotta take_cup_from_weight plc vent",
        "weighing close slider1 pos1",
        "cobotta put_cup_to_arc plc gateOpen",
        "slider weight_pos weighing open",
        "slider put_cup_arc cobotta take_dose_from_weight",
        "plc gateClose slider1 shelf3",
        "plc pump cobotta put_dose_to_shelf2 weighing close",
        "slider arcinit",
        "plc buzz",
        "plc arcOn",
        "slider arc_cw_3",
        "plc arcOff",
        "plc wait20s",
        "plc autoFlip",
        "plc buzz",
        "plc arcOn",
        "slider arc_ccw_3",
        "plc arcOff",
        "plc wait20s",
        "plc autoFlip",
        "plc buzz",
        "plc arcOn",
        "slider arc_cw_3",
        "plc arcOff",
        "plc wait20s",
        "plc autoFlip",
        "plc buzz",
        "plc arcOn",
        "slider arc_ccw_3",
        "plc arcOff",        
        "plc wait20s",
        "plc vent slider pos1",
        "plc gateOpen",
        "slider take_cup_arc",
        "plc gateClose cobotta take_cup_from_arc",
        "slider1 weight_pos weighing open",
        "plc singlePump cobotta put_cup_to_weight",
        "weighing close"
    };
    
    // Test sequence for development & testing
    test_sequence_ = {
        "slider init cobotta init weighing init plc init",
        "slider1 shelf1 plc buzz",
        "weighing open slider1 weight_pos cobotta test",
        "slider init cobotta init weighing init plc init",
    };
}

std::string ProcessController::getCurrentStep() const {
    return current_step_;
}

void ProcessController::updateDeviceStatus(const std::string& action) {
    devices_.updateDeviceStatus(action);
}

std::string ProcessController::extractDeviceAction(const std::string& step, size_t index) const {
    std::vector<std::string> devices = {"weighing", "slider", "slider1", "plc", "cobotta"};
    
    size_t foundIndex = 0;
    for (const auto& device : devices) {
        size_t found = step.find(device);
        if (found != std::string::npos) {
            if (foundIndex == index) {
                return device + " action";
            }
            foundIndex++;
        }
    }

    return "Keyword not found at index " + std::to_string(index);
}

bool ProcessController::areDevicesReady() const {
    return devices_.checkDevices(Situation::STANDBY);
}

const std::vector<std::string>& ProcessController::getCurrentSequence() const {
    return is_test_mode_ ? test_sequence_ : production_sequence_;
}

std::string ProcessController::processRequest(const std::string& action) {
    // Update device status based on the action
    updateDeviceStatus(action);
    
    // Check if all devices are standby
    if (areDevicesReady()) {
        const auto& processArray = getCurrentSequence();
        
        // Check if current step matches expected step
        if (current_step_ == processArray[step_index_]) {
            step_index_++;
            
            if (step_index_ < processArray.size()) {
                // Move to next step
                current_step_ = processArray[step_index_];
                
                // Update device statuses for the new step
                for (size_t i = 0; i < 3; i++) {
                    std::string deviceAction = extractDeviceAction(current_step_, i);
                    if (!deviceAction.empty() && deviceAction.find("not found") == std::string::npos) {
                        updateDeviceStatus(deviceAction);
                    }
                }
                
                return "OK";
            } else {
                // Process completed
                current_step_ = "finished";
                return "Finished";
            }
        } else {
            // Step mismatch
            current_step_ = "Error";
            return "Error: step mismatch";
        }
    }
    
    // Devices not ready
    return "Waiting for devices";
}