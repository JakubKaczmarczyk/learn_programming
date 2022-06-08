cmake_minimum_required(VERSION 3.22)
project(struktura_projektu C)

set(CMAKE_C_STANDARD 23)

set(SOURCE_FILES
        src/prad.c)

add_executable(struktura_projektu_debug ${SOURCE_FILES} main.c)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(include)
