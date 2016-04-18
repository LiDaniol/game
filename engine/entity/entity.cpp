#include "entity.h"

sf::Vector2f Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
}

Sprite& Entity::getSprite()
{
	return spr;
}