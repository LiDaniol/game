#ifndef GAME_TILEMAP_H
#define GAME_TILEMAP_H

#define DEFAULT_VBOMARGIN 16

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../render/metatexture.h"
#include "../extra/mathutils.h"
#include "../io/configfile.h"
#include "tile.h"

struct TilemapProxy // Proxy for the operator[] method of Tilemap
{
	int& operator[](int index) const;
	int* at;
};

class Tilemap : public sf::Drawable
{
public:
	Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex);

	void loadFromFile(const std::string& confname);
	int colorMatch(const sf::Color& col);

	TilemapProxy operator[](int index);
	int& atVec(sf::Vector2u pos);
	int& atRaw(int at);

	void update(const sf::View& view, int margin = DEFAULT_VBOMARGIN); // margin is in tiles

	int getTilesize() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray buildVertexArray(const sf::IntRect& rect) const;

	unsigned int wid, hei, tilesize;
	MetaTexture& metatexture;
	sf::VertexArray vbo;

	sf::IntRect vboview;

	std::vector<Tile> tileList;

	bool wasTilemapChanged = false;
	std::vector<int> map; // tile IDs
};

#endif