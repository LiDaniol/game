#include "metatexture.h"

MetaTexture::MetaTexture() {}

MetaTexture::MetaTexture(std::vector<sf::Texture>& textures)
{
	create(textures);
}

void MetaTexture::create(std::vector<sf::Texture>& textures)
{
	// @TODO optimization - make a true packing algorithm
	sf::Vector2u totalsize;
	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		sf::Vector2u texsize = textures[i].getSize();
		totalsize.x += texsize.x;
		if (texsize.y > totalsize.y) totalsize.y = texsize.y;
	}

	tex.create(totalsize.x, totalsize.y);

	for (unsigned int i = 0, currentx = 0; i < textures.size(); ++i)
	{
		sf::Sprite spr;
		spr.setTexture(textures[i]);
		spr.setPosition(currentx, 0);

		tex.draw(spr);

		tiles.push_back(sf::FloatRect(currentx, 0, textures[i].getSize().x, textures[i].getSize().y));
		currentx += textures[i].getSize().x;
	}
}

sf::FloatRect& MetaTexture::getTile(unsigned int index)
{
	return tiles[index];
}

sf::RenderTexture& MetaTexture::getMetaTexture()
{
	return tex;
}

const sf::Texture& MetaTexture::getTexture()
{
	return tex.getTexture();
}