#pragma once
#include <string>
#include <chrono>

std::string to_postgresql_timestamp(const std::chrono::time_point<std::chrono::system_clock>& tp);
std::chrono::time_point<std::chrono::system_clock> from_postgresql_timestamp(const std::string& timestamp_str);