cmake_minimum_required(VERSION 3.5.1)
project(mp3convert)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -Wextra")

set(CMAKE_C_FLAGS_DEBUG "-g -DIS_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DIS_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(mp3convert main.cpp)