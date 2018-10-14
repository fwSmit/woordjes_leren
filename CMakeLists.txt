cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project (woordjes_leren)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#include the necessary libraries
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(TGUI 0.7)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
	message(WARNING "Could not find TGUI")
endif()

include_directories(${SFML_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

set (CMAKE_CXX_STANDARD 11)
add_executable(woordjes_leren main.cpp)

target_link_libraries(woordjes_leren ${SFML_LIBRARIES})
