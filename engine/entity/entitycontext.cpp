#include "entitycontext.h"

Entity& EntityContext::operator[](int index)
{
	return entities[index];
}