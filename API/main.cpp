#include "crow.h"
#include "Controllers/auth_controller.h"
#include "Repos/token_repo.h"
#include "Helpers/token_helper.h"
#include "Controllers/incoming_text_controller.h"
#include "Helpers/twilio_helper.h"
#include "Interfaces/i_message_helper.h"
#include <unordered_map>

int main()
{
    crow::SimpleApp app;
    app.port(std::getenv("PORT") ? std::stoi(std::getenv("PORT")) : 8080);
    // Setup the token cache
    TokenRepo token_repo(getenv("DATABASE_CONNECTION_STRING")); 
    TokenHelper token_helper(token_repo);
    // Setup message repo
    MessageRepo message_repo(getenv("DATABASE_CONNECTION_STRING"));

    // Setup all controllers
    AuthController auth_controller(app, token_helper);
    IncomingTextController incoming_text_controller(app);
    incoming_text_controller.registerHandler("twilio", std::make_shared<TwilioHelper>(getenv("TWILIO_AUTH_TOKEN"), getenv("TWILIO_API_KEY"),message_repo));

    // run the app
    app.multithreaded().run();
}