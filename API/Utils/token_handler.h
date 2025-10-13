#pragma once
#include <string>
#include <unordered_map>

class TokenHandler {
    private:
        const std::string DB_CONN_STRING;
    public:
        explicit TokenHandler(const std::string db_conn_str);
        bool store_token(const std::string service_name, int user_id, const std::string& access_token, const std::string& refresh_token);
        std::unordered_map<std::string,std::string> get_token_for_user(const std::string service_name, int user_id);
};