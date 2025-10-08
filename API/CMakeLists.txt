cmake_minimum_required(VERSION 3.21)
project(job-application-handler-api CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add vcpkg toolchain if not integrated globally
# set(CMAKE_TOOLCHAIN_FILE "/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(Crow CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(job-application-handler-api 
    test.cpp
    Utils/encrypt.cpp
)

target_link_libraries(job-application-handler-api PRIVATE
    Crow::Crow asio::asio
    cpr::cpr
    jwt-cpp::jwt-cpp
    libpqxx::pqxx
    OpenSSL::SSL
    OpenSSL::Crypto
)
