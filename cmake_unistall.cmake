
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

file(REMOVE "${CMAKE_INSTALL_PREFIX}/bin/dex")
message(STATUS "Uninstalled: ${CMAKE_INSTALL_PREFIX}/bin/dex")
