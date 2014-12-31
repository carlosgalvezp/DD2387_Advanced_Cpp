project(Lab3)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")

file(GLOB SOURCES src/*.cpp src/objects/*.cpp src/places/*.cpp src/characters/*.cpp src/utils/*.cpp)
file(GLOB HEADERS include/*.h include/*.hpp include/objects/*.h include/places/*.h include/characters/*.h include/utils/*.h include/utils/ui_option.h)
include_directories(include)
add_executable(${PROJECT_NAME} src/apps/main.cpp ${SOURCES} ${HEADERS})
#target_link_libraries(${PROJECT_NAME} curses)
