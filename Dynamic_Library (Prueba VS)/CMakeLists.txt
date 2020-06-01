cmake_minimum_required(VERSION 3.16)
project(Dynamic_Library)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(main Threads::Threads)

