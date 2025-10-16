#include "twilio_helper.h"
#include "../Interfaces/i_message_helper.h"
#include "../Utils/form_parser.h"
#include <string>
#include <unordered_map>
#include "../Repos/message_repo.h"

TwilioHelper::TwilioHelper(std::string twilioApiKey, std::string twilioApiSecret, MessageRepo& messageRepo): 
_twilioApiKey(std::move(twilioApiKey)),
_twilioApiSecret(std::move(twilioApiSecret)),
_messageRepo(messageRepo)
{};   
bool TwilioHelper::processIncomingMessage(const crow::request& req) {
    // Extract apiKey and message from the request
    std::string apiKey = req.headers.find("X-Twilio-Signature") -> second;
    // validate the api key
    if(apiKey != _twilioApiKey) {
        return false;
    }
    // get canonical message
    Message msg = toCanonicalMessage(req.body);
    // store the message
    _messageRepo.upsert_message(msg);
    
    return true;
}

Message TwilioHelper::toCanonicalMessage(const std::string& body) {
    Message msg;
    msg.service_name = "twilio";
    std::unordered_map<std::string, std::string> form = parse_urlencoded_form(body);
    
    msg.content = form["body"];
    msg.sender = form["from"];
    msg.recipient = form["to"];
    msg.service_message_id = form["SmsSid"];
    return msg;
}