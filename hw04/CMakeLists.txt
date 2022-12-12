cmake_minimum_required(VERSION 3.0.0)
project(dialog_optimism_checkers)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(is_optimistic_parallelized)
add_subdirectory(is_optimistic_synchronized)
add_subdirectory(utils)

message("IS_OPTIMISTIC_PARALLELIZED_LIB_INCLUDE_DIRS = ${IS_OPTIMISTIC_PARALLELIZED_LIB_INCLUDE_DIRS}")
message("IS_OPTIMISTIC_PARALLELIZED_LIB_LIBRARIES = ${IS_OPTIMISTIC_PARALLELIZED_LIB_LIBRARIES}")
message("IS_OPTIMISTIC_SYNCHRONIZED_LIB_INCLUDE_DIRS = ${IS_OPTIMISTIC_SYNCHRONIZED_LIB_INCLUDE_DIRS}")
message("IS_OPTIMISTIC_SYNCHRONIZED_LIB_LIBRARIES = ${IS_OPTIMISTIC_SYNCHRONIZED_LIB_LIBRARIES}")
message("UTILS_LIB_INCLUDE_DIRS = ${UTILS_LIB_INCLUDE_DIRS}")
message("UTILS_LIB_LIBRARIES = ${UTILS_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -std=c++17")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -fprofile-arcs -ftest-coverage")

target_include_directories(${PROJECT_NAME} PUBLIC ${IS_OPTIMISTIC_PARALLELIZED_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IS_OPTIMISTIC_PARALLELIZED_LIB_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${IS_OPTIMISTIC_SYNCHRONIZED_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IS_OPTIMISTIC_SYNCHRONIZED_LIB_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${UTILS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${UTILS_LIB_LIBRARIES})



find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


add_subdirectory(tests)