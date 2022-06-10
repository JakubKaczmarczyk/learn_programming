cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID conditional_compilation)

include(../SetCommonConfig.cmake)

set(c_standards 90 99)
foreach (c_std IN LISTS c_standards)
    set(EXEC_DEBUG_C_OLD ${PROJECT_ID}__debug_C${c_std})
    add_executable(${EXEC_DEBUG_C_OLD} main.c)
    set_property(TARGET ${EXEC_DEBUG_C_OLD} PROPERTY C_STANDARD ${c_std})
endforeach ()
