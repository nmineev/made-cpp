##cmake_minimum_required(VERSION 3.0.0)
##project(matrix_calc VERSION 0.1.0)
##
##file(GLOB SOURCES "include/*.cpp" "app/*.cpp")
##file(GLOB INCLUDE_DIRS include)
##
##add_executable(${PROJECT_NAME} ${SOURCES})
##target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
##
##message("SOURCES = ${SOURCES}")
#
#
#cmake_minimum_required(VERSION 3.0.0)
#project(matrix_calc VERSION 0.1.0)
#
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)
## For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O2 -Wall -Werror -Wsign-compare")
#
#add_subdirectory(include)
#
#message("MATRIX_CALC_LIB_INCLUDE_DIRS = ${MATRIX_CALC_LIB_INCLUDE_DIRS}")
#message("MATRIX_CALC_LIB_LIBRARIES = ${MATRIX_CALC_LIB_LIBRARIES}")
#
#add_executable(${PROJECT_NAME} app/main.cpp tests/test_matrix_calc.cpp)
#
#target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_CALC_LIB_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${MATRIX_CALC_LIB_LIBRARIES})
#
#add_subdirectory(tests)

cmake_minimum_required(VERSION 3.0.0)
project(matrix)

add_subdirectory(include)

message("MATRIX_LIB_INCLUDE_DIRS = ${MATRIX_LIB_INCLUDE_DIRS}")
message("MATRIX_LIB_LIBRARIES = ${MATRIX_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} app/main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATRIX_LIB_LIBRARIES})

add_subdirectory(tests)