cmake_minimum_required(VERSION 3.14)
project(test_set)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -fprofile-arcs -ftest-coverage -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O0 -Wall -Werror -Wsign-compare")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage")

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SET_LIB_LIBRARIES} GTest::gtest_main)
