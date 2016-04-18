#include "entitycontext.h"

Entity& EntityContext::addEntity()
{
	entities.push_back(Entity());
	return entities[entities.size() - 1];
}

Entity& EntityContext::operator[](int index)
{
	return entities[index];
}