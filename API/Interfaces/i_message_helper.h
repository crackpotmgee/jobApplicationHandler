#pragma once
#include <string>
#include <crow.h>

class IMessageHelper {
public:
    virtual ~IMessageHelper() = default; 

    IMessageHelper();

    virtual bool processIncomingMessage(const crow::request& req) = 0;
};
