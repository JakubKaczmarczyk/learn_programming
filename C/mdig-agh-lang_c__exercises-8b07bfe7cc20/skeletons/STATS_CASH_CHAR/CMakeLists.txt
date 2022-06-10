cmake_minimum_required(VERSION 3.22)
project(STATS_CASH_CHAR C)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
add_executable(STATS_CASH_CHAR main.c)
