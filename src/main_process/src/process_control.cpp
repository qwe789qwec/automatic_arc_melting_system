#include "main_process/process_control.hpp"

ProcessController::ProcessController(bool is_test_mode)
    : current_step_("slider init cobotta init weighing init plc init"), 
      step_index_(0), 
      is_test_mode_(is_test_mode) {
    
    // Initialize device state manager
    devices_.addDevice(Instrument::WEIGHING);
    devices_.addDevice(Instrument::COBOTTA);
    devices_.addDevice(Instrument::SLIDER);
    devices_.addDevice(Instrument::PLC);
    devices_.initialized = true;
    
    // Initialize process sequences
    initializeProcessSequences();
}

void ProcessController::initializeProcessSequences() {
    // Production sequence
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
    
    // Test sequence
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

std::string ProcessController::processDeviceAction(const std::string& action) {
    // Update device status
    devices_.updateDeviceStatus(action);
    return "Status updated";
}

bool ProcessController::areAllDevicesStandby() const {
    return devices_.checkDevices(Situation::STANDBY);
}

std::string ProcessController::extractDeviceAction(const std::string& step, size_t index) const {
    std::vector<std::string> devices = {"weighing", "slider", "slider1", "plc", "cobotta"};
    
    size_t found_index = 0;
    for (const auto& device : devices) {
        size_t found = step.find(device);
        if (found != std::string::npos) {
            if (found_index == index) {
                return device + " action";
            }
            found_index++;
        }
    }

    return ""; // Device not found
}

bool ProcessController::isSequenceCompleted() const {
    return step_index_ >= getCurrentSequence().size();
}

bool ProcessController::isTestMode() const {
    return is_test_mode_;
}

const std::vector<std::string>& ProcessController::getCurrentSequence() const {
    return is_test_mode_ ? test_sequence_ : production_sequence_;
}

std::string ProcessController::moveToNextStep() {
    // Get the current sequence in use
    const auto& current_sequence = getCurrentSequence();
    
    // Check if current step matches the expected step in the sequence
    if (current_step_ == current_sequence[step_index_]) {
        // Move to the next step
        step_index_++;
        
        if (step_index_ < current_sequence.size()) {
            // Update current step
            current_step_ = current_sequence[step_index_];
            
            // Update device states to active
            for (size_t i = 0; i < 3; i++) {
                std::string device_action = extractDeviceAction(current_step_, i);
                if (!device_action.empty()) {
                    devices_.updateDeviceStatus(device_action);
                }
            }
            
            return "OK";
        } else {
            // Process complete
            current_step_ = "finished";
            return "Finished";
        }
    } else {
        // Step mismatch
        return "Error: Step mismatch";
    }
}