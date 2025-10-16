#pragma once
#include <string>
#include "../Models/message.h"
#include <vector>

class MessageRepo {
private:
    const std::string DB_CONN_STRING;
public:
    explicit MessageRepo(const std::string db_conn_str);
    Message& upsert_message(Message& message);
    std::vector<Message> get_messages_for_user(const std::string user_id, int limit=50);

};