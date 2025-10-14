#pragma once
#include <string>

class User {
public:
    int id;
    std::string google_sub;
    std::string email;
    std::string name;
    std::string picture;
    long long created_at;
    long long last_login;

    User();
    User(int id, const std::string& google_sub, const std::string& email, const std::string& name, const std::string& picture, long long created_at, long long last_login);
};