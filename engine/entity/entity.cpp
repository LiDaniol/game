#include "entity.h"
#include "../engine.h"

Entity::Entity(Engine& e) : engine(e) {}

sf::Vector2f Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
	if (spr) spr->setPosition(newPosition);
}

Sprite& Entity::createSprite()
{
	spr = new Sprite(*engine.getMetaTexture());
	return *spr;
}

Sprite* Entity::getSprite()
{
	return spr;
}