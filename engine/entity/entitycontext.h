#ifndef GAME_ENTITYCONTEXT_H
#define GAME_ENTITYCONTEXT_H

#include "entity.h"
#include <vector>

class EntityContext
{
public:
	Entity& addEntity();
	Entity& operator[](int index);

private:
	std::vector<Entity> entities;
};

#endif