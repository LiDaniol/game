#include "entitycontext.h"
#include "../engine.h"

EntityContext::EntityContext(Engine& e) : engine(e) {}

Entity& EntityContext::addEntity()
{
	entities.push_back(Entity(engine));
	return entities[entities.size() - 1];
}

Entity& EntityContext::operator[](int index)
{
	return entities[index];
}