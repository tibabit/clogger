cmake_minimum_required(VERSION 2.6)

# ----------------------------------------
# CLogger
# ----------------------------------------
project(clogger C)

add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Wcast-align)
add_definitions(-w)
add_definitions(-DDEBUG)

file(GLOB_RECURSE CLOGGER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c)


include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(clogger STATIC ${CLOGGER_SOURCES})

# ----------------------------------------
# clogger tests
# ----------------------------------------
file(GLOB_RECURSE CLOGGERR_TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/test/*.c)

add_executable(clogger_test ${CLOGGERR_TEST_SOURCES})
target_link_libraries (clogger_test clogger)
