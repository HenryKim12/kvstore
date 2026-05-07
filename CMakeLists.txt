cmake_minimum_required(VERSION 3.10)
project(KVStore VERSION 1.0)

# Enforce Modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tell CMake where to find your header files
include_directories(include)

# Compile the executable
add_executable(kvstore src/main.cpp src/store.cpp)
