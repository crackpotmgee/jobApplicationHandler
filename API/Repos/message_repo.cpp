#include "message_repo.h"
#include <pqxx/pqxx>
#include <iostream>
#include "../Utils/sql_converters.h"

MessageRepo::MessageRepo(const std::string db_conn_str): 
DB_CONN_STRING(db_conn_str){}

Message& MessageRepo::upsert_message(Message& message){
    try{
        
        pqxx::connection C(DB_CONN_STRING);
        pqxx::work W(C);
        pqxx::result res = W.exec("INSERT INTO platform_message (service_name, service_message_id, sender, recipient, content, direction, timestamp) VALUES ($1, $2, $3, $4, $5, $6, NOW()) RETURNING id, timestamp",
                        pqxx::params(message.service_name, message.service_message_id, message.sender, message.recipient, message.content, message.direction));
        
        if(!res.empty()) {
            std::string timeString = res.at(0)["timestamp"].as<std::string>();
            message.timestamp = from_postgresql_timestamp(timeString);
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