#include <stdlib.h>
#include <iostream>

#include "tilemap.h"

Tilemap::Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex) : wid(wid), hei(hei), tilesize(tilesize), metatexture(tex), tiles(wid * hei) {
	for (auto& i : tiles)
		i = rand() % 3;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(vbo, states);
}

void Tilemap::update(const sf::View& view, int margin)
{
	sf::IntRect newView((view.getCenter().x - (view.getSize().x / 2.f)) / tilesize,
						(view.getCenter().y - (view.getSize().y / 2.f)) / tilesize,
						(view.getSize().x) / tilesize,
						(view.getSize().y) / tilesize); // @TODO Handle rotations & all the shizzle because SFML.

	const sf::Vector2i topleft(newView.left, newView.top),
			           bottomright(newView.left + newView.width, newView.top + newView.height);
	if (wasTilemapChanged || !vboview.contains(topleft) || !vboview.contains(bottomright)) // if a VBO update is required
	{
		vboview = sf::IntRect(std::max(0, newView.left - margin),
				              std::max(0, newView.top - margin),
				              std::min(static_cast<int>(wid), newView.width + (margin * 2)),
				              std::min(static_cast<int>(hei), newView.height + (margin * 2)));

		vbo = buildVertexArray(vboview);
	}
}

int& Tilemap::at(sf::Vector2u pos)
{
	return tiles[pos.x + (pos.y * wid)];
}

sf::VertexArray Tilemap::buildVertexArray(const sf::IntRect& rect) const
{
	sf::VertexArray vbo(sf::Quads, rect.width * rect.height * 4); // Amount of tiles * tilesize

	for(int x = rect.left, xl = 0; x < std::min(10, rect.left + rect.width); ++x, ++xl)
	for(int y = rect.top, yl = 0; y < std::min(10, rect.top + rect.height); ++y, ++yl)
	{
		const unsigned int vloc = (xl + (yl * rect.width)) * 4, // VBO location
						   rloc = (x + (y * wid)); // Tileset location
		if (tiles[rloc] != -1) // air
		{
			vbo[vloc].position     = sf::Vector2f(x * tilesize,       y * tilesize);
			vbo[vloc + 1].position = sf::Vector2f((x + 1) * tilesize, y * tilesize);
			vbo[vloc + 2].position = sf::Vector2f((x + 1) * tilesize, (y + 1) * tilesize);
			vbo[vloc + 3].position = sf::Vector2f(x * tilesize,       (y + 1) * tilesize);

			const sf::FloatRect texrect = metatexture.getTile(tiles[rloc]);
			vbo[vloc].texCoords     = sf::Vector2f(texrect.left, texrect.top);
			vbo[vloc + 1].texCoords = sf::Vector2f(texrect.left + texrect.width, texrect.top);
			vbo[vloc + 2].texCoords = sf::Vector2f(texrect.left + texrect.width, texrect.top + texrect.height);
			vbo[vloc + 3].texCoords = sf::Vector2f(texrect.left, texrect.top + texrect.height);
		}
	}

	return vbo;
}