#include "tilemap.h"

int& TilemapProxy::operator[](int index) const
{
	return at[index];
}

Tilemap::Tilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex) : wid(wid), hei(hei), tilesize(tilesize), metatexture(tex), map(wid * hei) { }

void Tilemap::loadFromFile(const std::string& confname)
{
	vbo.clear();

	Config cfg;
	cfg.open(confname);

	sf::Image imgmap;
	imgmap.loadFromFile(cfg.getStringValue("mapfile").value);

	sf::Vector2u mapsize = imgmap.getSize();

	wid = mapsize.x; hei = mapsize.y;

	for (unsigned int x = 0; x < imgmap.getSize().x; ++x)
	for (unsigned int y = 0; y < imgmap.getSize().y; ++y)
	{
		map[x + (y * wid)] = colorMatch(imgmap.getPixel(x, y));
	}
}

int Tilemap::colorMatch(const sf::Color &col)
{
	for (unsigned int i = 0; i < tileList.size(); ++i)
		if (col == tileList[i].col) return i;

	return -1;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(vbo, states);
}

void Tilemap::update(const sf::View& view, int margin)
{
	sf::IntRect newView((view.getCenter().x - (view.getSize().x / 2.f)) / tilesize,
						(view.getCenter().y - (view.getSize().y / 2.f)) / tilesize,
						(view.getSize().x) / tilesize,
						(view.getSize().y) / tilesize);

	sf::IntRect maprect(0, 0, wid, hei);

	newView = clip(newView, maprect);

	const sf::Vector2i topleft(newView.left, newView.top),
			           bottomright(newView.left + newView.width, newView.top + newView.height);
	if (wasTilemapChanged || !vboview.contains(topleft) || !vboview.contains(bottomright)) // if a VBO update is required
	{
		vboview = sf::IntRect(newView.left - margin,
				              newView.top - margin,
				              newView.width + (margin * 2),
				              newView.height + (margin * 2));
		vboview = clip(vboview, maprect);

		vbo = buildVertexArray(vboview);
	}
}

int Tilemap::getTilesize() const
{
	return tilesize;
}

TilemapProxy Tilemap::operator[](int index)
{
	return TilemapProxy{&map[index * wid]};
}

int& Tilemap::atVec(sf::Vector2u pos)
{
	return map[pos.x + (pos.y * wid)];
}

int& Tilemap::atRaw(int at)
{
	return map[at];
}

sf::VertexArray Tilemap::buildVertexArray(const sf::IntRect& rect) const
{
	sf::VertexArray vbo(sf::Quads, rect.width * rect.height * 4); // Amount of tiles * vertice per square

	for(int x = rect.left, xl = 0; x < std::min(static_cast<int>(wid), rect.left + rect.width); ++x, ++xl)
	for(int y = rect.top, yl = 0; y < std::min(static_cast<int>(hei), rect.top + rect.height); ++y, ++yl)
	{
		const unsigned int vloc = (xl + (yl * rect.width)) * 4, // VBO location
						   rloc = (x + (y * wid)); // Tileset location
		if (map[rloc] != -1) // air
		{
			vbo[vloc].position     = sf::Vector2f(x * tilesize,       y * tilesize);
			vbo[vloc + 1].position = sf::Vector2f((x + 1) * tilesize, y * tilesize);
			vbo[vloc + 2].position = sf::Vector2f((x + 1) * tilesize, (y + 1) * tilesize);
			vbo[vloc + 3].position = sf::Vector2f(x * tilesize,       (y + 1) * tilesize);

			const sf::FloatRect texrect = metatexture.getTexRect(map[rloc]);
			vbo[vloc].texCoords     = sf::Vector2f(texrect.left, texrect.top);
			vbo[vloc + 1].texCoords = sf::Vector2f(texrect.left + texrect.width, texrect.top);
			vbo[vloc + 2].texCoords = sf::Vector2f(texrect.left + texrect.width, texrect.top + texrect.height);
			vbo[vloc + 3].texCoords = sf::Vector2f(texrect.left, texrect.top + texrect.height);
		}
	}

	return vbo;
}