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
add_definitions(-std=c99)
add_definitions(-g)

file(GLOB_RECURSE CLOGGER_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE CLOGGER_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")


include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(clogger STATIC ${CLOGGER_SOURCES})

install(DIRECTORY include/ DESTINATION include/clogger)
install(TARGETS clogger DESTINATION lib)

# ----------------------------------------
# clogger tests
# ----------------------------------------
add_subdirectory(test)
