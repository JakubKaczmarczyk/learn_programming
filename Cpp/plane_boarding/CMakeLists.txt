cmake_minimum_required(VERSION 3.22)
project(plane_boarding)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wconversion)


include_directories(include)
include_directories(C:/Program\ Files/xd/hehe)
include_directories(C:/Program\ Files/MySQL/Connector\ C++\ 8.0/include/jdbc)
include_directories(C:/Program\ Files/MySQL/MySQL\ Server\ 8.0/include)
link_directories(C:/Program\ Files/MySQL/Connector\ C++\ 8.0/lib64/vs14)
link_directories(C:/Program\ Files/MySQL/MySQL\ Server\ 8.0/lib)


set(SOURCE_FILES
        src/seats_rows.cpp
        src/passenger.cpp
        src/board.cpp
        src/simulation.cpp)

add_executable(plane_boarding_debug ${SOURCE_FILES} main.cpp)
add_executable(db_debug ${SOURCE_FILES} db_main.cpp)

target_link_libraries(db_debug C:/Program\ Files/MySQL/Connector\ C++\ 8.0/lib64/vs14/mysqlcppconn.lib)
target_link_libraries(db_debug C:/Program\ Files/MySQL/MySQL\ Server\ 8.0/lib/libmysql.lib)



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
