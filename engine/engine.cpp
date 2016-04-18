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

	if (!fullscreen && globalclock.getElapsedTime().asSeconds() > 1)
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
	std::vector<sf::Texture> texlist(conf.getStringArrayMatchCount(key));

	task << "Loading textures from configuration file..." << endl;

	for (unsigned int i = 0; i < texlist.size(); ++i)
	{
		std::vector<StringValue> tile = conf.getArrayValue(key, i).values; // @TODO make this more efficient
		info << ' ' << tile[0].value << endl;
		texlist[i].loadFromFile(tile[0].value);
	}

	task << "Generating metatexture... ";
	meta = new MetaTexture(texlist);
	std::cout << meta->getTexture().getSize().x << "x" << meta->getTexture().getSize().y << endl;
}

MetaTexture* Engine::getMetaTexture() const { return meta; }

void Engine::loadConfig(const std::string& file)
{
	conf.open(file);

	if (conf.getStringValue("vsync").asBool())
	{
		info << "VSync activated" << endl;
		window.setVerticalSyncEnabled(true);
	}

	if (conf.getStringValue("fullscreen").asBool())
	{
		fullscreen = true;

		int wid = conf.getStringValue("fwidth").parse(0, std::stoi), hei = conf.getStringValue("fheight", 0).parse(0, std::stoi);
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
		int wid = conf.getStringValue("wwidth").parse(800, std::stoi), hei = conf.getStringValue("wheight").parse(600, std::stoi);

		task << "Window size update... ";
		window.setSize(sf::Vector2u(wid, hei));
		std::cout << "Done." << endl;
	}

	vbomargin = conf.getStringValue("vbomargin").parse(16, std::stoi);
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