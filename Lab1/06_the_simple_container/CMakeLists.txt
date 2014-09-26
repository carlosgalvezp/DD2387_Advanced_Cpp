project(SimpleContainer)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
aux_source_directory(. SRC_LIST)
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

