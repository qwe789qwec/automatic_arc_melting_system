#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include "data_record/data_record.hpp"
#include "ros2_utils/service_utils.hpp"

namespace fs = std::filesystem;
using namespace std::chrono;

data_record::data_record(std::string path)
    : file_path(path)
{   
    fs::create_directories(file_path);
}

bool data_record::record(std::string message)
{
    const auto now = system_clock::now();
    const std::string filename = getDateString(now) + ".txt";
    const std::string filePath = baseDir / filename;

    std::ofstream outfile(filePath, std::ios::app);
    if (!outfile.is_open()) {
        throw std::runtime_error("Can't open the file: " + filePath);
    }

    outfile << getTimeString(now) << " | " << message << "\n";
}

std::string data_record::getDateString(const system_clock::time_point& tp) {
    const time_t t = system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

std::string data_record::getTimeString(const system_clock::time_point& tp) {
    const auto milliseconds = duration_cast<milliseconds>(tp.time_since_epoch()) % 1000;
    const time_t t = system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S") 
        << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}
