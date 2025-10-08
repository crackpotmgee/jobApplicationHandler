#include <pqxx/pqxx>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
class token_handler {
    public: bool store_token(const std::string& service_name, int user_id, const std::string& access_token, const std::string& refresh_token, const std::string& db_conn_str){
            try{
                pqxx::connection C(db_conn_str);
                pqxx::work W(C);
                W.exec_params("INSERT INTO token_cache (service_name, user_id, access_token, refresh_token, expires_at) VALUES ($1, $2, $3, $4, NOW() + INTERVAL '1 hour') ON CONFLICT (service_name, user_id) DO UPDATE SET access_token = EXCLUDED.access_token, refresh_token = EXCLUDED.refresh_token, expires_at = EXCLUDED.expires_at",
                              service_name, user_id, access_token, refresh_token);
                W.commit();
                return true;
            }
            catch(const std::exception& e){
                std::cerr << "Error storing token: " << e.what() << std::endl;
            }
        }
    };
    
