#include <pqxx/pqxx>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include "Utils/encrypt.h"
class token_handler {
    public: bool store_token(const std::string& service_name, int user_id, const std::string& access_token, const std::string& refresh_token, const std::string& db_conn_str){
        try{
            //encrypt the token
            std::string encrypted_access_token = encrypt_string(access_token);
            std::string encrypted_refresh_token = encrypt_string(refresh_token);
        
            pqxx::connection C(db_conn_str);
            pqxx::work W(C);
            W.exec_params("INSERT INTO token_cache (service_name, user_id, access_token, refresh_token, expires_at) VALUES ($1, $2, $3, $4, NOW() + INTERVAL '1 hour') ON CONFLICT (service_name, user_id) DO UPDATE SET access_token = EXCLUDED.access_token, refresh_token = EXCLUDED.refresh_token, expires_at = EXCLUDED.expires_at",
                            service_name, user_id, encrypted_access_token, encrypted_refresh_token);
            W.commit();
            return true;
        }
        catch(const std::exception& e){
            std::cerr << "Error storing token: " << e.what() << std::endl;
        }
        }
    };
    
