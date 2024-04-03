cmake_minimum_required(VERSION 3.21)
project(Hashtable)

set(CMAKE_CXX_STANDARD 20)

add_executable(Hashtable main.cpp cmake-build-debug/HASHTABLE.cpp cmake-build-debug/HASHTABLE.h cmake-build-debug/LESSON.cpp cmake-build-debug/LESSON.h)
