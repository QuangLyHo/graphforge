cmake_minimum_required(VERSION 3.20)
project(graphforge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(graphforge INTERFACE)
target_include_directories(graphforge INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(gf apps/gf.cpp)
target_link_libraries(gf PRIVATE graphforge)

