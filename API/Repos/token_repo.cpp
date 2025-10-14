#include <pqxx/pqxx>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include "../Utils/encrypt.h"
#include "token_repo.h"
#include "../Models/token.h"

TokenRepo::TokenRepo(const std::string db_conn_str): 
DB_CONN_STRING(db_conn_str){}

bool TokenRepo::store_token(Token& token){
    try{
        
        pqxx::connection C(DB_CONN_STRING);
        pqxx::work W(C);
        W.exec("INSERT INTO token_cache (service_name, user_id, access_token, refresh_token, expires_at) VALUES ($1, $2, $3, $4, NOW() + INTERVAL '1 hour') ON CONFLICT (service_name, user_id) DO UPDATE SET access_token = EXCLUDED.access_token, refresh_token = EXCLUDED.refresh_token, expires_at = EXCLUDED.expires_at",
                        pqxx::params(token.service_name, token.user_id, token.access_token, token.refresh_token));
        W.commit();
        return true;
    }
    catch(const std::exception& e){
        std::cerr << "Error storing token: " << e.what() << std::endl;
    }
    return false;
}
    
Token TokenRepo::get_token_for_user(const std::string service_name, int user_id){
    try{
    
        pqxx::connection C(DB_CONN_STRING);
        pqxx::work W(C);

        pqxx::result R = W.exec("SELECT access_token, refresh_token, expires_at from token_cache where user_id = $1 and service_name = $2 order by expires_at desc LIMIT 1", pqxx::params(user_id, service_name));

        // create result
        Token result;

        
        if(R.empty()) return result;
        
        pqxx::row first = R[0];
        result.user_id = first["user_id"].as<int>();
        result.access_token= first["access_token"].as<std::string>();
        result.refresh_token= first["refresh_token"].as<std::string>();
        //result.created_at = first["created_at"].as<std::chrono::time_point<std::chrono::steady_clock>>();
        //result.expires_at = first["expires_at"].as<std::chrono::time_point<std::chrono::steady_clock>>();
        //result.updated_at = first["updated_at"].as<std::chrono::time_point<std::chrono::steady_clock>>();
        
        return result;
    }
    catch(const std::exception& e){
        std::cerr << "Error accessing token: " << e.what() << std::endl;
        throw(e);
    }
}