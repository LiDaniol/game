#ifndef ONI_BINPACK_H_INCLUDED
#define ONI_BINPACK_H_INCLUDED

/*
 * This code originates from onidev and is published under the MIT license. It may be found here : https://github.com/onidev/BinPack
 * It was also changed/improved for this project.
 *
 * 	MIT license:
 * Copyright (c) 2015 Marmontel Boris
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

class BinPacker
{
public:
	BinPacker();

	virtual bool process(std::vector<sf::FloatRect> & rects) = 0;

protected:
	bool binpack(std::vector<sf::FloatRect> & rects, int wid, int hei) const;
	bool preprocess(std::vector<sf::FloatRect> & rects, int & minWid, int & minHei, int maxWid, int maxHei);

	std::vector<int> index;
};

class PowerOfTwoBinPacker : public BinPacker
{
	int maxWid;
	int maxHei;
	int m_width;
	int m_height;

public:
	PowerOfTwoBinPacker();
	PowerOfTwoBinPacker(int maxWid, int maxHei);

	bool process(std::vector<sf::FloatRect> & rects);
	int width() const;
	int height() const;
};

#endif
