#include "tilemap.h"

Tilemap::Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex) : wid(wid), hei(hei), tilesize(tilesize), metatexture(tex) {}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray vbo = buildVertexArray(); // @TODO : only build once
	target.draw(vbo);
}

sf::VertexArray Tilemap::buildVertexArray() const
{
	sf::VertexArray vbo(sf::Quads, wid * hei * 4); // Amount of tiles * tilesize

	for(unsigned int x = 0; x < wid; ++x)
	for(unsigned int y = 0; y < hei; ++y)
	{
		const unsigned int loc = x + (y * wid);
		const sf::FloatRect texrect;
		vbo[loc]     = sf::Vertex(sf::Vector2f(x * tilesize,            y * tilesize),            sf::Vector2f(texrect.left, texrect.top));										// Top left
		vbo[loc + 1] = sf::Vertex(sf::Vector2f(x * tilesize + tilesize, y * tilesize),            sf::Vector2f(texrect.left + texrect.width, texrect.top));						// Top right
		vbo[loc + 2] = sf::Vertex(sf::Vector2f(x * tilesize + tilesize, y * tilesize + tilesize), sf::Vector2f(texrect.left + texrect.width, texrect.top + texrect.height));	// Bottom right
		vbo[loc + 3] = sf::Vertex(sf::Vector2f(x * tilesize,            y * tilesize + tilesize), sf::Vector2f(texrect.left, texrect.top + texrect.height));					// Bottom left
	}
}

unsigned int& Tilemap::at(sf::Vector2u pos)
{
	return tiles[pos.x + (pos.y * wid)];
}