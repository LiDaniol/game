cmake_minimum_required(VERSION 3.5)
project(game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(sfml-system sfml-window sfml-graphics)

set(SOURCE_FILES main.cpp engine/engine.h engine/engine.cpp engine/tilemap.h engine/tilemap.cpp engine/metatexture.h engine/metatexture.cpp engine/configfile.h engine/configfile.cpp engine/stringutils.h engine/stringutils.cpp)
add_executable(game ${SOURCE_FILES})