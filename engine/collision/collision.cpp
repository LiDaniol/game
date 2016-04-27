#include "collision.h"

BoundingBox::BoundingBox(sf::FloatRect shape) : rect(shape) {}

sf::FloatRect BoundingBox::getRect() const
{
	return rect;
}

void BoundingBox::setRect(sf::FloatRect newRect)
{
	rect = newRect;
}

bool BoundingBox::collides(const BoundingBox& other)
{
	sf::FloatRect otherRect = other.getRect();

	return (rect.left < otherRect.left + otherRect.width) &&
		   (rect.left + rect.width > otherRect.left) &&
		   (rect.top < otherRect.top + otherRect.height) &&
		   (rect.height + rect.top > otherRect.top);
}