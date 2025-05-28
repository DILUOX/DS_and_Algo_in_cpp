cmake_minimum_required(VERSION 3.20)
project(BinaryExpressionTree)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

add_executable(BinaryExpressionTree main.cpp  BinaryExpressionTree.hpp
        stack.h
        exceptions.h
)
