#pragma once
#include <string>
#include <chrono>

class Token{
public:
    std::string service_name;
    int user_id;
    std::string access_token;
    std::string refresh_token;
    std::chrono::time_point<std::chrono::system_clock> expires_at;
    std::chrono::time_point<std::chrono::system_clock> created_at;
    std::chrono::time_point<std::chrono::system_clock> updated_at;

    Token();
    Token(std::string service_name,
        int user_id,
        std::string access_token,
        std::string refresh_token,
        std::chrono::time_point<std::chrono::system_clock> expires_at,
        std::chrono::time_point<std::chrono::system_clock> created_at,
        std::chrono::time_point<std::chrono::system_clock> updated_at
    );

};