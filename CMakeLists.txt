cmake_minimum_required(VERSION 3.24.2)
project(Europebet)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Europebet
        main.cpp
        ProductDatabase.cpp
        ProductDatabase.h)
add_definitions(-DNDEBUG)