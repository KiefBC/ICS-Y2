cmake_minimum_required(VERSION 3.29)
project(lab6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab6
        main.cpp
        main.h
        TestSuite.cpp
        TestSuite.h
        Point.cpp
        Tetromino.cpp)
