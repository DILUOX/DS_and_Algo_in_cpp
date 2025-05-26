cmake_minimum_required(VERSION 3.26)
project(dynamic_stack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

add_executable(dynamic_stack main.cpp
        stack.h
        stack.cpp
        exceptions.h
                )
