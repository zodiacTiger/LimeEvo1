cmake_minimum_required(VERSION 3.15)
project(LimeEvo1)
set(CMAKE_CXX_FLAGS -std=c++11)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)
include_directories(${PROJECT_SOURCE_DIR} src include)