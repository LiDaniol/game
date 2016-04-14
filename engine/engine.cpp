#include "engine.h"

Engine::Engine() : window(sf::VideoMode(800, 600), "Game Engine")
{
	window.setVerticalSyncEnabled(true);
}

Engine::~Engine()
{
	if (map != nullptr) delete map;
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

	window.display();
}

void Engine::addTileMap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex)
{
	map = new Tilemap(wid, hei, tilesize, tex);
}

void Engine::loadConfig(const std::string& file)
{
	conf.open(file);
}

Config& Engine::getConfig()
{
	return conf;
}