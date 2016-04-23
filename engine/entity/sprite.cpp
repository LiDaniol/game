#include "sprite.h"

/**** SpriteLayer ****/

SpriteLayer::SpriteLayer(Sprite* spr, int frameid, sf::FloatRect rect, sf::Vector2f offset) : mainspr(spr), offset(offset), rect(rect), frameid(frameid)
{
	sf::FloatRect sprrect = spr->getMeta().getTexRect(frameid);

	vbo.resize(4);
	update(rect);

	vbo[0].texCoords = sf::Vector2f(sprrect.left + rect.left, sprrect.top + rect.top); // Top left
	vbo[1].texCoords = sf::Vector2f(sprrect.left + rect.left + rect.width,  sprrect.top + rect.top); // Top right
	vbo[2].texCoords = sf::Vector2f(sprrect.left + rect.left + rect.width, sprrect.top + rect.top + rect.height); // Bottom right
	vbo[3].texCoords = sf::Vector2f(sprrect.left + rect.left, sprrect.top + rect.top + rect.height); // Bottom left
}

void SpriteLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = transform * mainspr->getTransform();
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
	return transform;
}

void SpriteLayer::setOffset(sf::Vector2f newOffset)
{
	offset = newOffset;
}

sf::Vector2f SpriteLayer::getOffset()
{
	return offset;
}

/**** Sprite ****/

Sprite::Sprite(MetaTexture& tex) : tex(tex) {}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const SpriteLayer& layer : layers)
	{
		target.draw(layer, states);
	}
}

SpriteLayer& Sprite::addSpriteLayer(int frameid, sf::FloatRect rect)
{
	layers.push_back(SpriteLayer(this, frameid, rect));
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

sf::Transform& Sprite::getTransform()
{
	return masterTransform;
}
