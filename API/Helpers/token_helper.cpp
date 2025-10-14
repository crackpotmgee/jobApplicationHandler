#include <pqxx/pqxx>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include "../Utils/encrypt.h"
#include "token_helper.h"
#include "../Repos/token_repo.h"
#include "../Models/token.h"

TokenHelper::TokenHelper(TokenRepo& tokenRepoInstance): 
_tokenRepo(tokenRepoInstance){}

bool TokenHelper::encrypt_and_store_token(const std::string service_name, int user_id, const std::string& access_token, const std::string& refresh_token){

    //encrypt the token
    std::string encrypted_access_token = encrypt_string(access_token);
    std::string encrypted_refresh_token = encrypt_string(refresh_token);

    Token encyptedToken(service_name, user_id, encrypted_access_token, encrypted_refresh_token, std::chrono::time_point<std::chrono::steady_clock>::min(), std::chrono::time_point<std::chrono::steady_clock>::min(), std::chrono::time_point<std::chrono::steady_clock>::min());
    
    return _tokenRepo.store_token(encyptedToken);
}
    
Token TokenHelper::get_token_and_decrypt(const std::string service_name, int user_id){
    Token token = _tokenRepo.get_token_for_user(service_name, user_id);
    token.access_token = decrypt_string(token.access_token);
    token.refresh_token = decrypt_string(token.refresh_token);
    return token;
}