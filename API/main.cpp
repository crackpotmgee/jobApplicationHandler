#include "crow.h"
#include "Controllers/AuthController.h"
int main()
{
    crow::SimpleApp app;
    app.port(std::getenv("PORT") ? std::stoi(std::getenv("PORT")) : 8080);
    // Setup the token cache
    TokenHandler token_handler(getenv("DATABASE_CONNECTION_STRING")); 
    // create the new route
    AuthController auth_controller(app, token_handler);

    // run the app
    app.multithreaded().run();
}