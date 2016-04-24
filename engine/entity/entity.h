#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>

#include "sprite.h"

class Engine;

class Entity
{
public:
	Entity(Engine& e);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& newPosition);

	Sprite& createSprite();
	Sprite* getSprite();

private:
	sf::Vector2f position;

	Sprite* spr;

	Engine& engine;
};

#endif