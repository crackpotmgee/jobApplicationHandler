#include "twilio_helper.h"
#include "../Interfaces/i_message_helper.h"

TwilioHelper::TwilioHelper(std::string twilioApiKey, std::string twilioApiSecret): 
_twilioApiKey(std::move(twilioApiKey)),
_twilioApiSecret(std::move(twilioApiSecret))
{};   
bool TwilioHelper::processIncomingMessage(const crow::request& req) {
    // Extract apiKey and message from the request
    std::string apiKey = req.headers.find("X-Twilio-Signature") -> second;
    // validate the api key
    if(apiKey != _twilioApiKey) {
        return false;
    }
    
    
    return true;
}