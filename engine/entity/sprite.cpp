#include "sprite.h"

SpriteLayer::SpriteLayer(Sprite* spr) : mainspr(spr) {}

void SpriteLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = transformation;
	states.texture = mainspr->getTexture();

	target.draw(vbo, states);
}

sf::VertexArray& SpriteLayer::getVBO()
{
	return vbo;
}

sf::Transform& SpriteLayer::getTransform()
{
	return transformation;
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const SpriteLayer& layer : layers)
	{
		target.draw(layer, states);
	}
}

SpriteLayer& Sprite::addSpriteLayer()
{
	layers.push_back(SpriteLayer(this));
	return layers[layers.size() - 1];
}

sf::Texture* Sprite::getTexture() const
{
	return tex;
}