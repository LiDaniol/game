#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Sprite;

class SpriteLayer : public sf::Drawable
{
public:
	SpriteLayer(Sprite* spr);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray& getVBO();
	sf::Transform& getTransform();

private:
	sf::VertexArray vbo;
	sf::Transform transformation;

	Sprite* mainspr;
};

class Sprite : public sf::Drawable
{
public:
	Sprite(sf::Texture* tex);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	SpriteLayer& addSpriteLayer();
	SpriteLayer& operator[](int index);

	sf::Texture* getTexture() const;

private:
	std::vector<SpriteLayer> layers;
	sf::Texture* tex;
};

#endif