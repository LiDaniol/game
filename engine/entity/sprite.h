#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../metatexture.h"

class Sprite;

class SpriteLayer : public sf::Drawable
{
public:
	SpriteLayer(Sprite* spr, int frameid, sf::Vector2f offset = sf::Vector2f(0.f, 0.f));

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(const sf::FloatRect &texRect);

	void setOffset(sf::Vector2f offset); // Offset from original sprite
	sf::Vector2f getOffset();

	int getFrameID() const;
	void setFrameID(int newID);

	sf::VertexArray& getVBO();
	sf::Transform& getTransform();

private:
	sf::VertexArray vbo;
	sf::Transform transformation;

	Sprite* mainspr;

	sf::Vector2f offset; // Offset from main sprite

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

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;

private:
	sf::Vector2f position;

	std::vector<SpriteLayer> layers;
	MetaTexture& tex;
};

#endif