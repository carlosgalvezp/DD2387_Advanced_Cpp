project(Lab3)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h include/*.hpp)
include_directories(include)
add_executable(${PROJECT_NAME} src/apps/main.cpp ${SOURCES} ${HEADERS})

