#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "tilemap.h"

class Engine
{
public:
	Engine();
	~Engine(); // @TODO : Use smart pointers to avoid using a destructor

	bool loop();
	void render();

	void addTileMap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex);

private:
	sf::RenderWindow window;
	Tilemap* map;
};

#endif