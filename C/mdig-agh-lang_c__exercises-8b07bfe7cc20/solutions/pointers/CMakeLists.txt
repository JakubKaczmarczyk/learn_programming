cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID pointers)

set(SOURCE_FILES
        src/ptrlib.c
        )

set(SOURCES_FILES_TESTS
        test/test_ptrlib.cpp
        )

include(../SetCommonConfig.cmake)
