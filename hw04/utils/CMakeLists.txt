cmake_minimum_required(VERSION 3.0.0)
project(utils)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -fprofile-arcs -ftest-coverage -fPIC -O0 -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage")

file(GLOB SOURCES is_optimistic.cpp main.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} is_optimistic.cpp)

set(UTILS_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(UTILS_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

add_executable(is_optimistic main.cpp)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})