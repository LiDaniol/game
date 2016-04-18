#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>

#include "sprite.h"

class Entity
{
public:
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& newPosition);

	Sprite& getSprite();

private:
	sf::Vector2f position;

	Sprite spr;
};

#endif