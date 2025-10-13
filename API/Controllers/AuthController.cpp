#include <crow.h>
#include <cpr/cpr.h>
#include <jwt-cpp/jwt.h>
#include <pqxx/pqxx>
#include "AuthController.h"
#include "../Utils/safe_getenv.h"
#include "../Utils/token_handler.h"
#include <jwt-cpp/traits/nlohmann-json/traits.h>



AuthController::AuthController(crow::SimpleApp& app, TokenHandler& tokenHandlerInstance)
      : CLIENT_ID(safe_getenv("GOOGLE_CLIENT_ID")),
        CLIENT_SECRET(safe_getenv("GOOGLE_CLIENT_SECRET")),
        REDIRECT_URI(safe_getenv("GOOGLE_REDIRECT_URI")),
        GOOGLE_TOKEN_ENDPOINT_URI(safe_getenv("GOOGLE_TOKEN_ENDPOINT_URI")),
        GOOGLE_AUTH_ENDPOINT_URI(safe_getenv("GOOGLE_AUTH_ENDPOINT_URI")),
        GOOGLE_API_SCOPES(safe_getenv("GOOGLE_API_SCOPES")),
        _tokenHandler(tokenHandlerInstance)
  {

      CROW_ROUTE(app, "/auth/google/callback")
      ([this](const crow::request& req) {
          return this->google_callback(req);
      });

      CROW_ROUTE(app, "/auth/google/login")
      ([this](const crow::request& req) {
          return this->google_login(req);
      });
  }

crow::response AuthController::google_callback(const crow::request& req){
  auto code = req.url_params.get("code");
  if(!code) return crow::response(400, "no code");

  // exchange code for token
  auto r = cpr::Post(cpr::Url{GOOGLE_TOKEN_ENDPOINT_URI},
                      cpr::Payload{
                        {"client_id", CLIENT_ID},
                        {"client_secret", CLIENT_SECRET},
                        {"code", std::string(code)},
                        {"grant_type","authorization_code"},
                        {"redirect_uri", REDIRECT_URI}
                      });

  if(r.status_code != 200) return crow::response(500, "token exchange failed");

  auto json = crow::json::load(r.text);
  std::string id_token = json["id_token"].s();
  std::string access_token = json["access_token"].s();
  std::string refresh_token = json["refresh_token"].s(); 

  auto decoded = jwt::decode<jwt::traits::nlohmann_json>(id_token);

  std::string google_sub = decoded.get_payload_claim("sub").as_string();
  std::string email = decoded.get_payload_claim("email").as_string();

  
  bool saved = _tokenHandler.store_token("google", 1, access_token, refresh_token);

  return crow::response(200, "success");
}

crow::response AuthController::google_login(const crow::request& req) {
    // Build the query parameters
    std::stringstream url_stream;
    
    // Begin the URL construction
    url_stream << GOOGLE_AUTH_ENDPOINT_URI << "?"
               << "response_type=code" 
               << "&client_id=" << CLIENT_ID
               << "&redirect_uri=" << REDIRECT_URI
               << "&scope=" << GOOGLE_API_SCOPES
               << "&access_type=offline"
               << "&prompt=consent"; 
    
    std::string redirect_url = url_stream.str();

    // redirect response
    crow::response res;
    res.code = 302;
    res.add_header("Location", redirect_url);
    
    return res;
}
