#pragma once
#include <string>
#include <crow.h>
#include "../Interfaces/i_message_helper.h"
#include <unordered_map>

class IncomingTextController {
    private:
        std::unordered_map<std::string, std::shared_ptr<IMessageHelper>> _message_helpers;
    public:
        explicit IncomingTextController(crow::SimpleApp& app);
        void registerHandler(const std::string& serviceName, std::shared_ptr<IMessageHelper> handler);
        crow::response receiveText(const std::string& serviceName, const crow::request& req);
};