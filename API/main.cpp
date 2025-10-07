#include <crow.h>
#include <cpr/cpr.h>
#include <jwt-cpp/jwt.h>
#include <pqxx/pqxx>

// Config: from env or k8s secret
std::string CLIENT_ID = getenv("GOOGLE_CLIENT_ID");
std::string CLIENT_SECRET = getenv("GOOGLE_CLIENT_SECRET");
std::string REDIRECT_URI = getenv("GOOGLE_REDIRECT_URI");

crow::App app;

crow::response google_callback(const crow::request& req){
    auto code = req.url_params.get("code");
    if(!code) return crow::response(400, "no code");

    // exchange code for token
    auto r = cpr::Post(cpr::Url{"https://oauth2.googleapis.com/token"},
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

    auto decoded = jwt::decode(id_token);

    std::string google_sub = decoded.get_payload_claim("sub").as_string();
    std::string email = decoded.get_payload_claim("email").as_string();
    // upsert into DB with libpqxx
    // generate your own session JWT and return to client
    crow::json::wvalue out;
    out["token"] = "YOUR_APP_JWT_HERE";
    return crow::response{out};
}

int main(){
    CROW_ROUTE(app, "/auth/google/callback")(google_callback);
    app.port(8080).run();
}