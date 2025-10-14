#include <string>
#include <vector>
#include "../Models/user.h"

class UserRepo{
    private:
        const std::string _connectionString;
    public:
        explicit UserRepo(std::string connectionString);
        User get_user(int id);
        User upsert_user(User& user);
        std::vector<User> get_users();
};