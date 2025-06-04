if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

message(STATUS "Uninstalling from ${CMAKE_INSTALL_PREFIX}")

file(REMOVE "${CMAKE_INSTALL_PREFIX}/bin/dex")
