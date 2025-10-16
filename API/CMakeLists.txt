cmake_minimum_required(VERSION 3.21)
project(job-application-handler-api CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(Crow CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(uriparser CONFIG REQUIRED char wchar_t)

add_executable(job-application-handler-api 
    main.cpp
    Controllers/auth_controller.cpp
    Controllers/incoming_text_controller.cpp
    Helpers/twilio_helper.cpp
    Helpers/token_helper.cpp
    Repos/token_repo.cpp
    Repos/user_repo.cpp
    Repos/message_repo.cpp
    Models/token.cpp
    Models/user.cpp
    Models/message.cpp
    Utils/split_by_delimiter.cpp
    Utils/safe_getenv.cpp
    Utils/form_parser.cpp
    Utils/encrypt.cpp
    Utils/sql_converters.cpp
    Interfaces/i_message_helper.cpp
)

target_link_libraries(job-application-handler-api PRIVATE
    Crow::Crow
    asio::asio
    cpr::cpr
    nlohmann_json::nlohmann_json
    jwt-cpp::jwt-cpp
    libpqxx::pqxx
    OpenSSL::SSL
    OpenSSL::Crypto
)
target_link_libraries(job-application-handler-api PUBLIC
    uriparser::uriparser
)
