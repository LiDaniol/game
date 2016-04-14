#include "engine.h"

Engine::Engine() : window(sf::VideoMode(1366, 768), "Game Engine")
{
	std::cout << "Initializing engine..." << std::endl;
	window.setVerticalSyncEnabled(true);
}

Engine::~Engine()
{
	if (map != nullptr) delete map;
	if (meta != nullptr) delete meta;
}

bool Engine::loop()
{
	renderclock.restart();

	sf::Event ev;
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window.close();

		if (ev.type == sf::Event::Resized)
		{
			sf::View oldview = window.getView();
			oldview.setSize(window.getSize().x, window.getSize().y);
			view = oldview;
			window.setView(view);
		}
	}
	return window.isOpen();
}

void Engine::render()
{
	window.clear(sf::Color::Black);

	sf::RenderStates states;
	states.texture = &meta->getTexture();
	map->update(view);
	window.draw(*map, states);

	window.display();

	if (globalclock.getElapsedTime().asSeconds() > 1)
	{
		window.setTitle("Game Engine - FPS : " + std::to_string(1.f / renderclock.restart().asSeconds()));
		globalclock.restart();
	}
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
	std::cout << "Loading textures from configuration file..." << std::endl;
	for (unsigned int i = 0; i < texnames.size(); ++i)
	{
		std::cout << ' ' << texnames[i] << ".png" << std::endl;
		texlist[i].loadFromFile(texnames[i] + ".png");
	}

	std::cout << "Generating metatexture... ";
	meta = new MetaTexture(texlist);
	std::cout << meta->getTexture().getSize().x << "x" << meta->getTexture().getSize().y << std::endl;
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

void Engine::updateView(const sf::View& newView)
{
	view = newView;
	view.zoom(.5f);
	window.setView(view);
}

sf::View& Engine::getView()
{
	return view;
}

sf::RenderWindow& Engine::getWindow()
{
	return window;
}