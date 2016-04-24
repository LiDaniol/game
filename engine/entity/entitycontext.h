#ifndef GAME_ENTITYCONTEXT_H
#define GAME_ENTITYCONTEXT_H

#include "entity.h"
#include <vector>

class Entity;
class Engine;

class EntityContext
{
public:
	EntityContext(Engine& e);

	Entity& addEntity();
	Entity& operator[](int index);
	int size() const;

private:
	std::vector<Entity> entities;
	Engine& engine;
};

#endif