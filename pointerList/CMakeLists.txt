cmake_minimum_required(VERSION 3.26)
project(dynamic_list)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Werror -Wall -Wextra -pedantic")

include_directories(include)
set(SOURCES src/main.cpp)
add_executable(dynamic_list ${SOURCES}
        )
