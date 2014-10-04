project(Bool_Vector)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
#aux_source_directory(. SRC_LIST)
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.hpp ../07_the_template_vector/kth_cprog_template_container.hpp)
add_executable(BoolVectorTest ${SOURCES} ${HEADERS})

