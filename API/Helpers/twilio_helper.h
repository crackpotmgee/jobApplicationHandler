#pragma once
#include <string>
#include "../Interfaces/i_message_helper.h"
#include <crow.h>

class TwilioHelper : public IMessageHelper {
private:
    std::string _twilioApiKey;
    std::string _twilioApiSecret;
public:
    bool processIncomingMessage(const crow::request& req);
    explicit TwilioHelper(std::string twilioApiKey,std::string twilioApiSecret);
};