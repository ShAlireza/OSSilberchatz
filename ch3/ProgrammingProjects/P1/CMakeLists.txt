cmake_minimum_required(VERSION 3.0)
project(shell C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")  # Example flags

add_subdirectory(utils)
add_subdirectory(core)
