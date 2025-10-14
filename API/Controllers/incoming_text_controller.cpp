#include "incoming_text_controller.h"
#include "../Helpers/twilio_helper.h"
#include <string>
#include <crow.h>

IncomingTextController::IncomingTextController(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/<string>/message").methods("POST"_method)([this](const crow::request& req, const std::string& serviceName) {
        return this->receiveText(serviceName,req);
    });
}

void IncomingTextController::registerHandler(const std::string& serviceName, std::shared_ptr<IMessageHelper> handler) {
    _message_helpers[serviceName] = std::move(handler);
}

crow::response IncomingTextController::receiveText(const std::string& serviceName, const crow::request& req) {
    // route the correct helper function
    IMessageHelper* handler = _message_helpers[serviceName].get();
    if(handler == nullptr) {
        return crow::response(404, "Service not found");
    }
    bool success = handler->processIncomingMessage(req);
    if(!success) {
        return crow::response(500, "Message processing failed");
    }
    return crow::response(200, "Message processed");
}