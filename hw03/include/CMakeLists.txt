cmake_minimum_required(VERSION 3.0.0)
project(set_lib)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage")

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(SET_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(SET_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
