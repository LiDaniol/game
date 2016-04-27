#ifndef GAME_TILE_H
#define GAME_TILE_H

#include <SFML/Graphics.hpp>
#include <string>

struct Tile
{
	int frameid;
	sf::Color col;
	std::string name;
};

#endif