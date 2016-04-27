#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <SFML/Graphics.hpp>

class BoundingBox
{
public:
	BoundingBox(sf::FloatRect shape);

	sf::FloatRect getRect();
	void setRect(sf::FloatRect newRect);

private:
	sf::FloatRect rect;
};

#endif