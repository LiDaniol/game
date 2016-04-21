#include "sprite.h"

SpriteLayer::SpriteLayer(Sprite* spr, int frameid, sf::Vector2f offset) : mainspr(spr), offset(offset), frameid(frameid)
{
	sf::FloatRect texRect = mainspr->getMeta().getTexRect(frameid);

	vbo.resize(4);
	update(texRect);

	vbo[0].texCoords = sf::Vector2f(texRect.left, texRect.top); // Top left
	vbo[1].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top); // Top right
	vbo[2].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top + texRect.height); // Bottom right
	vbo[3].texCoords = sf::Vector2f(texRect.left, texRect.top + texRect.height); // Bottom left
}

void SpriteLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = transformation;
	states.texture = &mainspr->getMeta().getTexture();

	target.draw(vbo, states);
}

void SpriteLayer::update(const sf::FloatRect &texRect)
{
	sf::Vector2f mainpos = mainspr->getPosition() + offset;

	vbo[0].position = mainpos;
	vbo[1].position = mainpos + sf::Vector2f(texRect.width, 0);
	vbo[2].position = mainpos + sf::Vector2f(texRect.width, texRect.height);
	vbo[3].position = mainpos + sf::Vector2f(0, texRect.height);
}

int SpriteLayer::getFrameID() const
{
	return frameid;
}

void SpriteLayer::setFrameID(int newID)
{
	frameid = newID;
}

sf::VertexArray& SpriteLayer::getVBO()
{
	return vbo;
}

sf::Transform& SpriteLayer::getTransform()
{
	return transformation;
}

void SpriteLayer::setOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

sf::Vector2f SpriteLayer::getOffset()
{
	return offset;
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

void Sprite::setPosition(sf::Vector2f pos)
{
	position = pos;
	for (SpriteLayer& i : layers)
		i.update(tex.getTexRect(i.getFrameID()));
}

sf::Vector2f Sprite::getPosition() const
{
	return position;
}

Sprite::Sprite(MetaTexture& tex) : tex(tex) {}