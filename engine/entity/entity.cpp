#include "entity.h"
#include "../engine.h"

Entity::Entity(Engine& e) : engine(e) {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::cout << spr << " : " << static_cast<bool>(spr) << std::endl;
	if (spr) target.draw(*spr, states);
	//Sprite& sprite = *spr;
	std::cout << spr->getPosition().x << std::endl;
	//target.draw(sprite, states);
}

sf::Vector2f Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
	if (spr) spr->setPosition(newPosition);
}

Sprite* Entity::createSprite()
{
	spr = new Sprite(*engine.getMetaTexture());
	std::cout << spr << " : " << static_cast<bool>(spr) << std::endl;
	return spr;
}

Sprite* Entity::getSprite()
{
	return spr;
}