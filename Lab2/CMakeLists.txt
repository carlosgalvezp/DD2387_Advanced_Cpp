project(Lab2)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

file(GLOB SOURCES date.cpp gregorian.cpp julian.cpp kattistime.cpp)
file(GLOB HEADERS date.h gregorian.h julian.h kattistime.h calendar.h)

add_executable(${PROJECT_NAME} main.cpp  ${SOURCES} ${HEADERS})
#add_executable(datetest datetest.cpp  ${SOURCES} ${HEADERS})
add_executable(cprog09lab22a cprog09lab22a.cpp ${SOURCES} ${HEADERS})
add_executable(cprog09lab22b cprog09lab22b.cpp ${SOURCES} ${HEADERS})
add_executable(cprog09lab22c cprog09lab22c.cpp ${SOURCES} ${HEADERS})
add_executable(cprog09lab23  cprog09lab23.cpp  ${SOURCES} ${HEADERS})


