cmake_minimum_required(VERSION 3.0.0)
project(set)

add_subdirectory(include)

message("SET_LIB_INCLUDE_DIRS = ${SET_LIB_INCLUDE_DIRS}")
message("SET_LIB_LIBRARIES = ${SET_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage")

target_include_directories(${PROJECT_NAME} PUBLIC ${SET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SET_LIB_LIBRARIES})

add_subdirectory(tests)
