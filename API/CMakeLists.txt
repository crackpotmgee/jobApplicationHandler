cmake_minimum_required(VERSION 3.21)
project(JobApplicationHandlerAPI)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

find_package(fmt CONFIG REQUIRED)  

add_executable(JobApplicationHandlerAPI main.cpp)
target_link_libraries(JobApplicationHandlerAPI PRIVATE fmt::fmt)
