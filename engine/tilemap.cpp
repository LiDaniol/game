#include <stdlib.h>

#include "tilemap.h"

Tilemap::Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex) : wid(wid), hei(hei), tilesize(tilesize), metatexture(tex), tiles(wid * hei) {
	for (auto& i : tiles)
		i = rand() % 3;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(vbo, states);
}

void Tilemap::viewUpdate(const sf::View& view)
{
	//std::cout << "Running task for " << std::thread::hardware_concurrency() << " threads" << std::endl;
	// @TODO : Rebuild a VBO if necessary
}

int& Tilemap::at(sf::Vector2u pos)
{
	return tiles[pos.x + (pos.y * wid)];
}

sf::VertexArray Tilemap::buildVertexArray() const
{
	sf::VertexArray vbo(sf::Quads, wid * hei * 4); // Amount of tiles * tilesize

	for(unsigned int x = 0; x < wid; ++x)
		for(unsigned int y = 0; y < hei; ++y)
		{
			const unsigned int loc = (x + (y * wid)) * 4;
			if (tiles[loc / 4] != -1) // air
			{
				vbo[loc].position     = sf::Vector2f(x * tilesize,       y * tilesize);
				vbo[loc + 1].position = sf::Vector2f((x + 1) * tilesize, y * tilesize);
				vbo[loc + 2].position = sf::Vector2f((x + 1) * tilesize, (y + 1) * tilesize);
				vbo[loc + 3].position = sf::Vector2f(x * tilesize,       (y + 1) * tilesize);

				const sf::FloatRect texrect = metatexture.getTile(tiles[loc / 4]);
				vbo[loc].texCoords     = sf::Vector2f(texrect.left, texrect.top);
				vbo[loc + 1].texCoords = sf::Vector2f(texrect.left + texrect.width, texrect.top);
				vbo[loc + 2].texCoords = sf::Vector2f(texrect.left + texrect.width, texrect.top + texrect.height);
				vbo[loc + 3].texCoords = sf::Vector2f(texrect.left, texrect.top + texrect.height);
			}
		}

	return vbo;
}