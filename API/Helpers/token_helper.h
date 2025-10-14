#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../Models/token.h"
#include "../Repos/token_repo.h"

class TokenHelper {
    private:
        TokenRepo& _tokenRepo;
    public:
        explicit TokenHelper(TokenRepo& tokenRepoInstance);
        bool encrypt_and_store_token(const std::string service_name, int user_id, const std::string& access_token, const std::string& refresh_token);
        Token get_token_and_decrypt(const std::string service_name, int user_id);
};