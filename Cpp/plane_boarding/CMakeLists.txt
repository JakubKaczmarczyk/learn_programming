cmake_minimum_required(VERSION 3.22)
project(plane_boarding)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wconversion)

include_directories(include)

set(SOURCE_FILES
        src/seats_rows.cpp
        src/passenger.cpp
        src/board.cpp
        src/simulation.cpp)

add_executable(plane_boarding_debug ${SOURCE_FILES} main.cpp)


set(SOURCE_FILES_TESTS
        test/test_seat.cpp
        test/test_passenger.cpp
        test/test_board.cpp)

add_executable(plane_boarding_tests ${SOURCE_FILES_TESTS} ${SOURCE_FILES} test/main_gtest.cpp)

target_include_directories(plane_boarding_tests PUBLIC
        ../googletest-master/googlemock/include
        ../googletest-master/googletest/include
        )

add_subdirectory(../googletest-master googletest-master)

target_link_libraries(plane_boarding_tests gmock)
