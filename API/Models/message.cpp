#include "message.h"
#include <string>
#include <chrono>

Message::Message():
id(0),
service_name(""),
service_message_id(""),
sender(""),
recipient(""),
content(""),
direction(0),
timestamp(std::chrono::time_point<std::chrono::system_clock>::min()){}

Message::Message(int id, std::string service_name, std::string service_message_id, std::string sndr, std::string rcpt, std::string cntnt, int drct, std::chrono::time_point<std::chrono::system_clock> time):
id(id),
service_name(std::move(service_name)),
service_message_id(std::move(service_message_id)),
sender(std::move(sndr)),
recipient(std::move(rcpt)),
content(std::move(cntnt)),
direction(drct),
timestamp(time){}