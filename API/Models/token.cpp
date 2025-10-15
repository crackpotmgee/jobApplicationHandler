#include "token.h"

Token::Token():
service_name(""),
user_id(0),
access_token(""),
refresh_token(""),
expires_at(std::chrono::time_point<std::chrono::system_clock>::min()),
created_at(std::chrono::time_point<std::chrono::system_clock>::min()),
updated_at(std::chrono::time_point<std::chrono::system_clock>::min()){}

Token::Token(std::string service_name,
        int user_id,
        std::string access_token,
        std::string refresh_token,
        std::chrono::time_point<std::chrono::system_clock> expires_at,
        std::chrono::time_point<std::chrono::system_clock> created_at,
        std::chrono::time_point<std::chrono::system_clock> updated_at):
service_name(""),
user_id(0),
access_token(""),
refresh_token(""),
expires_at(std::chrono::time_point<std::chrono::system_clock>::min()),
created_at(std::chrono::time_point<std::chrono::system_clock>::min()),
updated_at(std::chrono::time_point<std::chrono::system_clock>::min()){}