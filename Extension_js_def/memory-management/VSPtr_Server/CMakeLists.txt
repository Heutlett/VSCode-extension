cmake_minimum_required(VERSION 3.16)
project(VSPtr_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(VSPtr_Server server.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(VSPtr_Server Threads::Threads)
