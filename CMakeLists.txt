cmake_minimum_required(VERSION 3.25)
project(Database_Application)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Database_Application
        main.cpp
        ProductDatabase.cpp
        ProductDatabase.h)
add_definitions(-DNDEBUG)