cmake_minimum_required(VERSION 3.0.0)
project(is_optimistic_parallelized)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -fprofile-arcs -ftest-coverage -fPIC -O0 -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage")

file(GLOB SOURCES *.hpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

set(IS_OPTIMISTIC_PARALLELIZED_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(IS_OPTIMISTIC_PARALLELIZED_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
