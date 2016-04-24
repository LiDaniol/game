project(game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

link_libraries(sfml-system sfml-window sfml-graphics)

#set(CMAKE_CXX_COMPILER "clang++")

set(SOURCE_FILES main.cpp engine/engine.h engine/engine.cpp engine/tilemap.h engine/tilemap.cpp engine/metatexture.h engine/metatexture.cpp engine/configfile.h engine/configfile.cpp engine/stringutils.h engine/stringutils.cpp engine/logger.h engine/logger.cpp engine/entity/entity.h engine/entity/entity.cpp engine/entity/sprite.h engine/entity/sprite.cpp engine/entity/entitycontext.h engine/entity/entitycontext.cpp engine/mathutils.h)
add_executable(game ${SOURCE_FILES})