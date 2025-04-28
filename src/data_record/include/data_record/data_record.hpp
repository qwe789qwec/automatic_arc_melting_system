#ifndef WEIGHING_MACHINE_HPP
#define WEIGHING_MACHINE_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>

class data_record
{
public:
    data_record(std::string path = "datalog");
    ~data_record();
    
    bool record(std::string message);

private:
    std::string get_date_string(const system_clock::time_point& tp);
    std::string get_time_string(const system_clock::time_point& tp);
    std::string file_path;
};

#endif // WEIGHING_MACHINE_HPP