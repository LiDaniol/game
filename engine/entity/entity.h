#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>

#include "../render/sprite.h"
#include "../collision/collision.h"

class Engine;

class Entity : public sf::Drawable
{
public:
	Entity(Engine& e);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& newPosition);

	std::unique_ptr<Sprite>& createSprite();
	std::unique_ptr<Sprite>& createSpriteFromEngineData(const std::string& spritename);
	std::unique_ptr<Sprite>& getSprite();

	std::unique_ptr<BoundingBox>& createBoundingBox(sf::FloatRect rect);
	std::unique_ptr<BoundingBox>& getBoundingBox();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f position;

	std::unique_ptr<Sprite> spr;
	std::unique_ptr<BoundingBox> box;

	Engine& engine;
};

#endif