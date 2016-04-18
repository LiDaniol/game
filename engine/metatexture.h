#ifndef GAME_METATEXTURE_H
#define GAME_METATEXTURE_H

#include <SFML/Graphics.hpp>
#include <vector>

class MetaTexture
{
public:
	MetaTexture();
	MetaTexture(std::vector<sf::Texture>& textures);

	MetaTexture& operator=(const MetaTexture& other);

	void create(std::vector<sf::Texture>& textures);

	sf::FloatRect& getTexRect(unsigned int index); // according to SFML wiki, some graphics drivers doesn't accept integer texture coordinates so avoid casting
	sf::RenderTexture& getMetaTexture();
	const sf::Texture& getTexture();

private:
	sf::RenderTexture tex;
	std::vector<sf::FloatRect> tiles;
};

#endif