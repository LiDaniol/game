#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../metatexture.h"

class Sprite;

class SpriteLayer : public sf::Drawable
{
public:
	SpriteLayer(Sprite* spr, int frameid);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray& getVBO();
	sf::Transform& getTransform();

private:
	sf::VertexArray vbo;
	sf::Transform transformation;

	Sprite* mainspr;

	int frameid;
};

class Sprite : public sf::Drawable
{
public:
	Sprite(MetaTexture& tex);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	SpriteLayer& addSpriteLayer(int frameid);
	SpriteLayer& operator[](int index);

	MetaTexture& getMeta();

private:
	std::vector<SpriteLayer> layers;
	MetaTexture& tex;
};

#endif