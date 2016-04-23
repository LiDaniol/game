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

std::vector<std::pair<std::vector<StringValue>, int>> Engine::importTextureConfig(const std::string &key)
{
	unsigned int resourceCount = conf.getCountArray(key), firstit = texlist.size();
	texlist.resize(firstit + resourceCount);

	std::vector<std::pair<std::vector<StringValue>, int>> remainingMatches(resourceCount); // Extra config key data

	task << "Loading texture batch with key '" << key << "'..." << endl;

	for (unsigned int i = 0; i < resourceCount; ++i)
	{
		std::vector<StringValue> texdata = conf.getArrayValue(key, i).values;
		info << ' ' << texdata[0].value << endl;
		texlist[i + firstit].loadFromFile(texdata[0].value);

		remainingMatches[i].second = i; // assign texture ID
		remainingMatches[i].first.resize(texdata.size() - 1);
		for (unsigned int j = 1; j < texdata.size(); ++j)
		{
			remainingMatches[i].first[j - 1] = texdata[j];
		}
	}

	return remainingMatches;
}

void Engine::generateTileConfig(const std::string& key)
{
	importTextureConfig(key);
}

void Engine::importSpritesConfig(const std::string& texkey, const std::string& layerkey)
{
	auto remainingData = importTextureConfig(texkey);

	sprdata.resize(remainingData.size());
	for (unsigned int i = 0; i < remainingData.size(); ++i)
	{
		sprdata[i].name = remainingData[i].first[0].value;
		sprdata[i].metaframe = remainingData[i].second;
	}

	unsigned int resourceCount = conf.getCountArray(layerkey);

	for (unsigned int i = 0; i < resourceCount; ++i)
	{
		std::vector<StringValue> layerdata = conf.getArrayValue(layerkey, i).values;
		SpriteData* data;

		for (unsigned int j = 0; j < sprdata.size(); ++j)
		{
			if (sprdata[j].name == layerdata[0].value)
			{
				data = &sprdata[j];
				break;
			}
		}

		if (data)
		{
			data->metarects.push_back(sf::FloatRect(layerdata[2].parse(0, std::stoi), // @TODO : use stof (and fix that parse method when using them)
			                                        layerdata[3].parse(0, std::stoi),
													layerdata[4].parse(0, std::stoi),
													layerdata[5].parse(0, std::stoi)));
		}
	}
}

void Engine::buildMeta()
{
	task << "Generating metatexture from imported textures... ";
	meta = new MetaTexture(texlist);
	texlist.clear();
	std::cout << meta->getTexture().getSize().x << "x" << meta->getTexture().getSize().y << endl;
}

MetaTexture* Engine::getMetaTexture() const { return meta; }

void Engine::loadConfig(const std::string& file)
{
	conf.open(file);

	if (conf.getStringValue("vsync", 0).asBool())
	{
		info << "VSync activated" << endl;
		window.setVerticalSyncEnabled(true);
	}

	if (conf.getStringValue("fullscreen", 0).asBool())
	{
		fullscreen = true;

		int wid = conf.getStringValue("fwidth", 0).parse(0, std::stoi), hei = conf.getStringValue("fheight", 0).parse(0, std::stoi);
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
		int wid = conf.getStringValue("wwidth", 0).parse(800, std::stoi), hei = conf.getStringValue("wheight", 0).parse(600, std::stoi);

		task << "Window size update... ";
		window.setSize(sf::Vector2u(wid, hei));
		std::cout << "Done." << endl;
	}

	vbomargin = conf.getStringValue("vbomargin", 0).parse(16, std::stoi);
	if (vbomargin != DEFAULT_VBOMARGIN)
	{
		info << "VBO view margin updated" << endl;
	}
}

Config& Engine::getConfig()
{
	return conf;
}

void Engine::updateView(const sf::View& newView, int preferredWidth)
{
	view = newView;

	// Determine best zoom level, if at least a tilemap is present
	if (map)
		view.zoom(1.f / static_cast<int>( view.getSize().x / (preferredWidth * map->getTilesize()) ));

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

EntityContext& Engine::getContext()
{
	return ctx;
}