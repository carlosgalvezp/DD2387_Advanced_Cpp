project(Matrix)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
#aux_source_directory(. SRC_LIST)
FILE(GLOB SOURCES Matrix.cpp matrix_test.cpp)
FILE(GLOB HEADERS Matrix.h)
add_executable(MyMatrixTest ${SOURCES} ${HEADERS})

