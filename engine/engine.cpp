#include "engine.h"

Engine::Engine() : window(sf::VideoMode(800, 600), "Game Engine")
{
	task << "Initializing engine..." << endl;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	return window.isOpen();
}

void Engine::render()
{
	window.clear(sf::Color::Black);

	sf::RenderStates states;
	states.texture = &meta->getTexture();
	map->update(view, vbomargin);
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

void Engine::generateTileConfig(const std::string& key)
{
	std::vector<sf::Texture> texlist(3); // @TODO, custom count ofc

	task << "Loading textures from configuration file..." << endl;

	int i = 0;
	while (true)
	{
		std::vector<std::string> tile = conf.getArrayValue(key, i);
		if (tile.size() > 0)
		{
			info << ' ' << tile[0] << endl; // @TODO : Add a getKeyCount method
			texlist[i].loadFromFile(tile[0]);
		}
		else
		{
			break;
		}

		i++;
	}

	task << "Generating metatexture... ";
	meta = new MetaTexture(texlist);
	std::cout << meta->getTexture().getSize().x << "x" << meta->getTexture().getSize().y << endl;
}

MetaTexture* Engine::getMetaTexture() const { return meta; }

void Engine::loadConfig(const std::string& file)
{
	conf.open(file);

	if (conf.getStringValue("vsync") == "true")
	{
		info << "VSync activated" << endl;
		window.setVerticalSyncEnabled(true);
	}

	if (conf.getStringValue("fullscreen") == "true")
	{
		int wid = std::stoi(conf.getStringValue("fwidth", 0, "0")), hei = std::stoi(conf.getStringValue("fheight", 0, "0"));
		task << "Switching to fullscreen mode... ";

		sf::VideoMode mode;
		if (!wid && !hei)
			mode = sf::VideoMode::getDesktopMode();
		else
			mode = sf::VideoMode(wid, hei);

		window.close();
		window.create(mode, "", sf::Style::Fullscreen);

		std::cout << "Done." << endl;
	}
	else
	{
		int wid = std::stoi(conf.getStringValue("wwidth", 0, "800")), hei = std::stoi(conf.getStringValue("wheight", 0, "600"));

		task << "Window size update... ";
		window.setSize(sf::Vector2u(wid, hei));
		std::cout << "Done." << endl;
	}

	vbomargin = std::stoi(conf.getStringValue("vbomargin", 0, "16"));
	if (vbomargin != DEFAULT_VBOMARGIN)
	{
		info << "VBO view margin updated" << endl;
	}
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