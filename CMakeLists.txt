cmake_minimum_required(VERSION 3.8)

project(Knapsack VERSION 1.0
    DESCRIPTION "Using different methods to solve 0-1 knapsack problem"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

option(DOUBLE "use double instead of int" OFF)

if(DOUBLE)
    add_definitions(-DUSE_DOUBLE)
endif()

include_directories(include)
aux_source_directory(src SRC_LIST)

foreach(algorithm IN LISTS SRC_LIST)
    get_filename_component(algorithm_name ${algorithm} NAME_WE)

    if(DOUBLE)
        set(algorithm_name ${algorithm_name}_double)
    endif()

    add_executable(${algorithm_name} main.cpp ${algorithm})
endforeach()
