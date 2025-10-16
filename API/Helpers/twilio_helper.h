#pragma once
#include <string>
#include "../Interfaces/i_message_helper.h"
#include <crow.h>
#include "../Models/message.h"
#include "../Repos/message_repo.h"

class TwilioHelper : public IMessageHelper {
private:
    std::string _twilioApiKey;
    std::string _twilioApiSecret;
    MessageRepo& _messageRepo;
    Message toCanonicalMessage(const std::string& body);
public:
    bool processIncomingMessage(const crow::request& req);
    explicit TwilioHelper(std::string twilioApiKey,std::string twilioApiSecret, MessageRepo& messageRepo);
};