cmake_minimum_required(VERSION 3.21)
project(job-application-handler-workers CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(job-application-handler-workers
    main.cpp
)

target_link_libraries(job-application-handler-workers PRIVATE
    
)
