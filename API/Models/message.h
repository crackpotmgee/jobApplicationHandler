#pragma once
#include <string>
#include <chrono>
class Message {
public:
    int id;
    std::string service_name;
    std::string service_message_id;
    std::string sender;
    std::string recipient;
    std::string content;
    std::chrono::time_point<std::chrono::system_clock> timestamp;

    Message();
    Message(int id, std::string service_name, std::string service_message_id, std::string sndr, std::string rcpt, std::string cntnt, std::chrono::time_point<std::chrono::system_clock> time);
};