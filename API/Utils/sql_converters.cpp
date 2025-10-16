#include "sql_converters.h"
#include <string>
#include <chrono>
#include <pqxx/pqxx>

std::string to_postgresql_timestamp(const std::chrono::time_point<std::chrono::system_clock>& tp) {
    auto in_time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::chrono::time_point<std::chrono::system_clock> from_postgresql_timestamp(const std::string& timestamp_str) {
    // Define the input format
    std::istringstream iss(timestamp_str);
    std::tm tm = {};
    
    // Parse the string into a tm structure
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    
    if (iss.fail()) {
        throw std::runtime_error("Failed to parse timestamp string.");
    }

    auto in_time_t = mktime(&tm);
    
    // Correct return: Convert the time_t directly to a system_clock time_point
    return std::chrono::system_clock::from_time_t(in_time_t);
}