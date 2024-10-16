cmake_minimum_required(VERSION 3.10)

# Set project name
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(main main.cpp Credit.cpp test.cpp)
