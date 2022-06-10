cmake_minimum_required(VERSION 3.22)
project(matrix C)

set(CMAKE_C_STANDARD 23)

add_executable(matrix main.c src/matrix.c include/matrix.h)


include_directories(include)