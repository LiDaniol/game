#ifndef GAME_MATHUTILS_H_H
#define GAME_MATHUTILS_H_H

#include <SFML/Graphics.hpp>

template<typename T>
sf::Rect<T> clip(sf::Rect<T>& a, sf::Rect<T>& b)
{
	return sf::Rect<T>(std::max(a.left, b.left),
					   std::max(a.top, b.top),
					   std::min(a.width, b.width),
					   std::min(a.height, b.height));
}

#endif