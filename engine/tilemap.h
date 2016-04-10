#ifndef GAME_TILEMAP_H
#define GAME_TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "metatexture.h"

class Tilemap : public sf::Drawable
{
public:
	Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex);

	unsigned int& at(sf::Vector2u pos);

	sf::VertexArray buildVertexArray() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	unsigned int wid, hei, tilesize;
	MetaTexture& metatexture;
	std::vector<unsigned int> tiles;
};

#endif