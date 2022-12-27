cmake_minimum_required(VERSION 3.0.0)
project(matrix_calc)

add_subdirectory(include)

message("MATRIX_CALC_LIB_INCLUDE_DIRS = ${MATRIX_CALC_LIB_INCLUDE_DIRS}")
message("MATRIX_CALC_LIB_LIBRARIES = ${MATRIX_CALC_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage" )

target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_CALC_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATRIX_CALC_LIB_LIBRARIES})

add_subdirectory(tests)
