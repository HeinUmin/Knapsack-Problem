cmake_minimum_required(VERSION 3.21)

project(Knapsack VERSION 1.0
    DESCRIPTION "Using different methods to solve 0-1 knapsack problem"
    LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

option(DOUBLE "use double instead of int" OFF)

if(DOUBLE)
    add_definitions(-DUSE_DOUBLE)
endif()

add_executable(dp src/dp.cpp src/knapsack.cpp src/knapsack.h)
add_executable(bt src/bt.cpp src/knapsack.cpp src/knapsack.h)
add_executable(bb src/bb.cpp src/knapsack.cpp src/knapsack.h)
