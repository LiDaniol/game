#ifndef GAME_TILEMAP_H
#define GAME_TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "metatexture.h"

class Tilemap : public sf::Drawable
{
public:
	Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex);

	int& at(sf::Vector2u pos);

	void viewUpdate(const sf::View& view);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray buildVertexArray() const;

	unsigned int wid, hei, tilesize;
	MetaTexture& metatexture;
	sf::VertexArray vbo;
	std::vector<int> tiles;
};

#endif