cmake_minimum_required(VERSION 3.21)
project(JobApplicationHandler CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add vcpkg toolchain if not integrated globally
# set(CMAKE_TOOLCHAIN_FILE "/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(crow CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

add_executable(job_application_handler main.cpp)

target_link_libraries(job_application_handler PRIVATE
    crow
    cpr::cpr
    jwt-cpp::jwt-cpp
    pqxx
)
