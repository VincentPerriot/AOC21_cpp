cmake_minimum_required(VERSION 3.1)

project(AOC_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(utils)
include_directories(puzzles)

file(GLOB_RECURSE PUZZLE_SOURCES puzzles/*.cpp)

foreach(PUZZLE_SOURCE IN LISTS PUZZLE_SOURCES)
    get_filename_component(PUZZLE_NAME ${PUZZLE_SOURCE} NAME_WE)
    add_executable(${PROJECT_NAME}_${PUZZLE_NAME} utils/io.cpp ${PUZZLE_SOURCE})
    
endforeach()
