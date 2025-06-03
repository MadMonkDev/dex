
cmake_minimum_required(VERSION 3.12)
project(dex)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)

file(GLOB SOURCES "src/*.c")
add_executable(dex ${SOURCES})
