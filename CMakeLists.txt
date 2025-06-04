
cmake_minimum_required(VERSION 3.12)
project(dex)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set version for packaging
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Include header files
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.c")

# Add executable
add_executable(dex ${SOURCES})

# Install target: puts binary in /usr/local/bin
install(TARGETS dex
    RUNTIME DESTINATION /usr/local/bin
)

# Create uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
