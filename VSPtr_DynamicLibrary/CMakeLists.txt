cmake_minimum_required(VERSION 3.15)
project(VSPtr_DynamicLibrary)

set(CMAKE_CXX_STANDARD 14)

add_library(VSPtr_DynamicLibrary SHARED garbageCollector.cpp garbageCollector.h VSPointer.h VSPointer.cpp garbageElement.h garbageElement.cpp CustomLinkedList.h Node.h client.h pointerParser.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(VSPtr_DynamicLibrary Threads::Threads)