#include <pqxx/pqxx>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include "encrypt.h"
#include "token_handler.h"

TokenHandler::TokenHandler(const std::string db_conn_str): 
DB_CONN_STRING(db_conn_str){}

bool TokenHandler::store_token(const std::string service_name, int user_id, const std::string& access_token, const std::string& refresh_token){
    try{
        //encrypt the token
        std::string encrypted_access_token = encrypt_string(access_token);
        std::string encrypted_refresh_token = encrypt_string(refresh_token);
    
        pqxx::connection C(DB_CONN_STRING);
        pqxx::work W(C);
        W.exec_params("INSERT INTO token_cache (service_name, user_id, access_token, refresh_token, expires_at) VALUES ($1, $2, $3, $4, NOW() + INTERVAL '1 hour') ON CONFLICT (service_name, user_id) DO UPDATE SET access_token = EXCLUDED.access_token, refresh_token = EXCLUDED.refresh_token, expires_at = EXCLUDED.expires_at",
                        service_name, user_id, encrypted_access_token, encrypted_refresh_token);
        W.commit();
        return true;
    }
    catch(const std::exception& e){
        std::cerr << "Error storing token: " << e.what() << std::endl;
    }
    return false;
}
    
std::unordered_map<std::string,std::string> TokenHandler::get_token_for_user(const std::string service_name, int user_id){
    try{
    
        pqxx::connection C(DB_CONN_STRING);
        pqxx::work W(C);
        pqxx::result R = W.exec_params("SELECT access_token, refresh_token, expires_at from token_cache where user_id = $1 and service_name = $2 order by expires_at desc LIMIT 1", user_id, service_name);

        // create result
        std::unordered_map<std::string,std::string> result;

        
        if(R.empty()) return result;
        
        pqxx::row first = R[0];
        result["access_token"]= first["access_token"].as<std::string>();
        result["refresh_token"]= first["refresh_token"].as<std::string>();
        
        return result;
    }
    catch(const std::exception& e){
        std::cerr << "Error accessing token: " << e.what() << std::endl;
        throw(e);
    }
}