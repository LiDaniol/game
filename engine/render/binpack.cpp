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

#include "binpack.h"
#include <algorithm>
#include <SFML/Graphics.hpp>

static int pow2ceil(int x)
{
	if (x < 0)
		return 0;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x+1;
}

namespace
{

	struct Node
	{
		Node * child[2];
		sf::FloatRect rc;
		bool full;

		Node() : full(false) { child[0] = child[1] = 0; }
		~Node() { delete child[0]; delete child[1]; }
		Node * insert(sf::FloatRect & rect);

		bool leaf() const { return child[0] == 0 && child[1] == 0; }
	};

	Node * Node::insert(sf::FloatRect & rect)
	{
		if(!leaf())
		{
			Node * newNode = child[0]->insert(rect);
			if(newNode)
				return newNode;
			else
				return child[1]->insert(rect);
		}
		else
		{
			if(full)
			{
				return 0;
			}

			// On regarde si le restangle rentre
			if(rect.width > rc.width || rect.height > rc.height)
			{
				return 0;
			}

			// Rentre parfaitement
			if(rect.width == rc.width && rect.height == rc.height)
			{
				full = true;
				rect.left = rc.left;
				rect.top = rc.top;
				return this;
			}

			// Sinon, on coupe la zone en deux parties
			// on regarde dans si l'on doit couper horizontalement ou verticalement
			int dw = rc.width - rect.width;
			int dh = rc.height - rect.height;

			if(dw > dh)
			{
				child[0] = new Node;
				child[0]->rc = sf::FloatRect(rc.left, rc.top, rect.width, rc.height);
				child[1] = new Node;
				child[1]->rc = sf::FloatRect(rc.left + rect.width, rc.top, dw, rc.height);
			}
			else
			{
				child[0] = new Node;
				child[0]->rc = sf::FloatRect(rc.left, rc.top, rc.width, rect.height);
				child[1] = new Node;
				child[1]->rc = sf::FloatRect(rc.left, rc.top + rect.height, rc.width, dh);
			}

			return child[0]->insert(rect);
		}
	}

} // namespace



// BinPacker base
BinPacker::BinPacker():
		index()
{
}

bool BinPacker::binpack(std::vector<sf::FloatRect> & rects, int wid, int hei) const
{
	Node root;
	root.rc = sf::FloatRect(0, 0, wid, hei);

	for(size_t i=0; i<index.size(); ++i)
	{
		if(!root.insert(rects[index[i]]))
			return false;
	}

	return true;
}

bool BinPacker::preprocess(std::vector<sf::FloatRect> & rects, int & minWid, int & minHei, int maxWid, int maxHei)
{
	// Check minimum area size
	minWid = 0;
	minHei = 0;
	for(sf::FloatRect & r: rects)
	{
		if(r.width> minWid) minWid = r.width;
		if(r.height > minHei) minHei = r.height;
	}

	// if limited size
	if(maxWid != 0 && maxHei != 0 && (minWid > maxWid || minHei > maxHei))
		return false;

	index.resize(rects.size());
	for(size_t i=0; i<rects.size(); ++i)
	{
		index[i] = i;
	}

	std::sort(index.begin(), index.end(), [&rects](int i, int j)
	{
		const sf::FloatRect & a = rects[i];
		const sf::FloatRect & b = rects[j];

		if(a.width > a.height)
		{
			return (a.width > b.width && a.width > b.height);
		}
		return (a.height > b.width && a.height > b.height);
	});

	return true;
}



PowerOfTwoBinPacker::PowerOfTwoBinPacker():
		maxWid(0), maxHei(0)
{
}

PowerOfTwoBinPacker::PowerOfTwoBinPacker(int maxWid, int maxHei):
		maxWid(maxWid), maxHei(maxHei)
{
}

bool PowerOfTwoBinPacker::process(std::vector<sf::FloatRect> & rects)
{
	int minWid, minHei;
	if(!preprocess(rects, minWid, minHei, maxWid, maxHei))
		return false;

	minWid = pow2ceil(minWid);
	minHei = pow2ceil(minHei)>>1;
	bool swap = false;

	while(true)
	{
		if(swap)
			minWid <<= 1;
		else
			minHei <<= 1;
		swap ^= 1;

		if(binpack(rects, minWid, minHei))
		{
			m_width = minWid;
			m_height = minHei;
			break;
		}
	}

	return true;
}

int PowerOfTwoBinPacker::width() const
{
	return m_width;
}
int PowerOfTwoBinPacker::height() const
{
	return m_height;
}