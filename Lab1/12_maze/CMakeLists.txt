project(MazeSolver)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
#aux_source_directory(. SRC_LIST)
FILE(GLOB SOURCES maze.cpp ../11_matrix/Matrix.cpp)
FILE(GLOB HEADERS ../11_matrix/Matrix.h)
add_executable(Maze ${SOURCES} ${HEADERS})

