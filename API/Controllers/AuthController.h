#pragma once
#include <crow.h>
#include "../Utils/token_handler.h"

class AuthController {
private:
    const std::string GOOGLE_API_SCOPES;
    const std::string CLIENT_ID;
    const std::string CLIENT_SECRET;
    const std::string REDIRECT_URI;
    const std::string GOOGLE_TOKEN_ENDPOINT_URI;
    const std::string GOOGLE_AUTH_ENDPOINT_URI;
    TokenHandler& _tokenHandler;
public:
    explicit AuthController(crow::SimpleApp& app, TokenHandler& tokenHandlerInstance);
    crow::response google_callback(const crow::request& req);
    crow::response google_login(const crow::request& req);
};