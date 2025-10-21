#ifndef PROCESS_CONTROL_HPP
#define PROCESS_CONTROL_HPP

#include <string>
#include <vector>
#include "main_process/devices_state.hpp"
#include <map>

struct Process {
    std::vector<std::string> sequence;
    size_t current_step = 0;
    DeviceStateManager device_manager;
};


class ProcessController {
public:
    explicit ProcessController();
    std::string getCurrentStep();
    int getCurrentStepNumber(int process_number) const;
    std::string updateDeviceStatuses(const std::string& command);
    bool isReadyToNextStep(int process_number) const;
    bool isSequenceCompleted(int process_number) const;
    void moveToNextStep(int process_number);
    void insertSequence(int process_number, std::vector<std::string> seq);
    
private:
    std::map<int, Process> sequences_;
    const std::vector<std::string> sequence_files_ = {
        "sequence/test_1.txt",
        "sequence/test_2.txt"
    };

    std::vector<std::string> getDevicesListFromStep(const std::string& step);
};

#endif // PROCESS_CONTROL_HPP