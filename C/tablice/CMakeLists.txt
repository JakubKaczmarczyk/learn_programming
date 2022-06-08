cmake_minimum_required(VERSION 3.22)
project(tablice)

set(CMAKE_C_STANDARD 23)


set(SOURCE_FILES
        src/source1.c)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
#add_compile_options(-Wall )

include_directories(include)

add_executable(tablice_debug ${SOURCE_FILES} main.c)
