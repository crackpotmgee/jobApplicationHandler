#include <string>
#include "user.h"

User::User():id(0), google_sub(""), email(""), name(""), picture(""), created_at(0), last_login(0) {}

User::User(int id, const std::string& google_sub, const std::string& email, const std::string& name, const std::string& picture, long long created_at, long long last_login)
    : id(id), google_sub(google_sub), email(email), name(name), picture(picture), created_at(created_at), last_login(last_login) {}
