#pragma once
#include <string>
#include "../Models/token.h"

class TokenRepo {
    private:
        const std::string DB_CONN_STRING;
    public:
        explicit TokenRepo(const std::string db_conn_str);
        bool store_token(Token& token);
        Token get_token_for_user(const std::string service_name, int user_id);
};