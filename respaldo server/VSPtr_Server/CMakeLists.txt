cmake_minimum_required(VERSION 3.16)
project(VSPtr_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(VSPtr_Server main.cpp)
target_link_libraries(VSPtr_Server ${CMAKE_SOURCE_DIR}/libVSPtr_DynamicLibrary.so)
