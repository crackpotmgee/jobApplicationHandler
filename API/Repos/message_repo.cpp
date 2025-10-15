#include "message_repo.h"
#include <pqxx/pqxx>
#include <iostream>

MessageRepo::MessageRepo(const std::string db_conn_str): 
DB_CONN_STRING(db_conn_str){}

Message& MessageRepo::upsert_message(Message& message){
    try{
        
        pqxx::connection C(DB_CONN_STRING);
        pqxx::work W(C);
        pqxx::result res = W.exec("INSERT INTO messages (service_name, service_message_id, sender, recipient, content, timestamp) VALUES ($1, $2, $3, $4, $5, NOW()) RETURNING id, timestamp",
                        pqxx::params(message.service_name, message.service_message_id, message.sender, message.recipient, message.content));
        
        if(!res.empty()) {
            message.timestamp = res.at(0)["timestamp"].as<std::chrono::time_point<std::chrono::system_clock>>();
            message.id = res.at(0)["id"].as<int>();
        }
        W.commit();
        return message;
    }
    catch(const std::exception& e){
        std::cerr << "Error storing message: " << e.what() << std::endl;
    }
    return message;
}