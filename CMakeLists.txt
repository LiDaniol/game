project(game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

link_libraries(sfml-system sfml-window sfml-graphics)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto")

set(SOURCE_FILES main.cpp engine/engine.h engine/engine.cpp engine/map/tilemap.h engine/map/tilemap.cpp engine/render/metatexture.h engine/render/metatexture.cpp engine/io/configfile.h engine/io/configfile.cpp engine/extra/stringutils.h engine/extra/stringutils.cpp engine/io/logger.h engine/io/logger.cpp engine/entity/entity.h engine/entity/entity.cpp engine/render/sprite.h engine/render/sprite.cpp engine/entity/entitycontext.h engine/entity/entitycontext.cpp engine/extra/mathutils.h)
add_executable(game ${SOURCE_FILES})