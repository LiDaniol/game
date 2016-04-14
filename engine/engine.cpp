#include "engine.h"

Engine::Engine() : window(sf::VideoMode(800, 600), "Game Engine")
{
	window.setVerticalSyncEnabled(true);
}

Engine::~Engine()
{
	if (map != nullptr) delete map;
	if (meta != nullptr) delete meta;
}

bool Engine::loop()
{
	sf::Event ev;
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window.close();
	}
	return window.isOpen();
}

void Engine::render()
{
	window.clear(sf::Color::Black);

	sf::RenderStates states;
	states.texture = &meta->getTexture();
	window.draw(*map, states);

	window.display();
}

void Engine::addTilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex)
{
	map = new Tilemap(wid, hei, tilesize, tex);
}

Tilemap* Engine::getTilemap() const { return map; }

void Engine::generateTextureConfig(const std::string& key)
{
	std::vector<std::string> texnames = conf.getArrayValue(key);
	std::vector<sf::Texture> texlist;

	texlist.resize(texnames.size());
	for (unsigned int i = 0; i < texnames.size(); ++i)
	{
		texlist[i].loadFromFile(texnames[i] + ".png");
	}

	meta = new MetaTexture(texlist);
}

MetaTexture* Engine::getMetaTexture() const { return meta; }

void Engine::loadConfig(const std::string& file)
{
	conf.open(file);
}

Config& Engine::getConfig()
{
	return conf;
}