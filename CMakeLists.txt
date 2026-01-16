cmake_minimum_required(VERSION 3.20)
project(graphforge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(graphforge INTERFACE)
target_include_directories(graphforge INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(gf apps/gf.cpp)
target_link_libraries(gf PRIVATE graphforge)

enable_testing()

add_executable(test_bfs tests/test_bfs.cpp)
target_link_libraries(test_bfs PRIVATE graphforge)
add_test(NAME bfs COMMAND test_bfs ${CMAKE_SOURCE_DIR}/graphs/tiny.txt)

add_executable(test_dfs tests/test_dfs.cpp)
target_link_libraries(test_dfs PRIVATE graphforge)
add_test(NAME dfs COMMAND test_dfs ${CMAKE_SOURCE_DIR}/graphs/tiny.txt)
