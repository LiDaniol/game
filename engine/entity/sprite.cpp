#include "sprite.h"

SpriteLayer::SpriteLayer(Sprite* spr, int frameid) : mainspr(spr), frameid(frameid) {}

void SpriteLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = transformation;
	states.texture = &mainspr->getMeta().getTexture();

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

SpriteLayer& Sprite::addSpriteLayer(int frameid)
{
	layers.push_back(SpriteLayer(this, frameid));
	return layers[layers.size() - 1];
}

SpriteLayer& Sprite::operator[](int index)
{
	return layers[index];
}

MetaTexture& Sprite::getMeta()
{
	return tex;
}

Sprite::Sprite(MetaTexture& tex) : tex(tex) {}