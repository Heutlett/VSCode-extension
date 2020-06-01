cmake_minimum_required(VERSION 3.15)
project(VSPtr_DynamicLibrary)

set(CMAKE_CXX_STANDARD 14)

add_library(VSPtr_DynamicLibrary SHARED library.h library.cpp garbageCollector.cpp garbageCollector.h VSPointer.h VSPointer.cpp garbageElement.h garbageElement.cpp person.cpp person.h)