#include "engine.h"

Engine::Engine() : window(sf::VideoMode(800, 600), "Game Engine"), ctx(*this) {}

void Engine::drawEntities(sf::RenderStates states)
{
	for (int i = 0; i < ctx.size(); ++i)
		window.draw(ctx[i], states);
}

bool Engine::loop()
{
	tickTimer.restart();

	sf::Event ev;
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window.close();

		if (ev.type == sf::Event::Resized)
		{
			sf::View oldview = window.getView();
			view = oldview;
			view.setSize(ev.size.width, ev.size.height);
			view.setCenter(sf::Vector2f(static_cast<int>(oldview.getCenter().x), static_cast<int>(oldview.getCenter().y)));
			window.setView(view);
		}

		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::R)
			{
				map->loadFromFile("maptest.conf");
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	return window.isOpen();
}

void Engine::render()
{
	window.clear(sf::Color(191, 133, 29));

	sf::RenderStates states;
	states.texture = &meta->getTexture();
	map->update(view, vbomargin);
	window.draw(*map, states);

	drawEntities(states);

	// Debug : show metatexture
	/*sf::Sprite spr;
	spr.setTexture(meta->getTexture());
	window.draw(spr);*/

	window.display();

	float fps = 1.f / tickTimer.restart().asSeconds();
	deltatime = (deltatime * .9f) + (.1f * (1.f / (fps / deltatarget))); // smoothed out delta time
	if (!fullscreen && titleUpdateTimer.getElapsedTime().asSeconds() > 1)
	{
		window.setTitle("Game Engine - FPS : " + std::to_string(fps));
		titleUpdateTimer.restart();
	}
}

void Engine::addTilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex)
{
	map = std::make_unique<Tilemap>(wid, hei, tilesize, tex);
	map->setTilelist(tileList);
}

std::unique_ptr<Tilemap>& Engine::getTilemap() { return map; }

std::vector<std::pair<std::vector<StringValue>, int>> Engine::importTextureConfig(const std::string &key)
{
	unsigned int resourceCount = conf.getCountArray(key), firstit = texlist.size();
	texlist.resize(firstit + resourceCount);

	std::vector<std::pair<std::vector<StringValue>, int>> remainingMatches(resourceCount); // Extra config key data

	task << "Loading texture batch with key '" << key << '\'' << endl;

	for (unsigned int i = 0; i < resourceCount; ++i)
	{
		std::vector<StringValue> texdata = conf.getArrayValue(key, i).values;
		info << "- " << texdata[0].value << endl;
		texlist[i + firstit].loadFromFile(texdata[0].value);

		remainingMatches[i].second = i + firstit; // assign texture ID
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
	auto remainingData = importTextureConfig(key);

	tileList.resize(remainingData.size());
	for (unsigned int i = 0; i < remainingData.size(); ++i)
	{
		tileList[i].name = remainingData[i].first[0].value;
		tileList[i].col = sf::Color(remainingData[i].first[1].parse(0), remainingData[i].first[2].parse(0), remainingData[i].first[3].parse(0), remainingData[i].first[4].parse(255));
		tileList[i].frameid = remainingData[i].second;
	}
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
		SpriteData* data = nullptr;

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
			data->layers.push_back(LayerData{ layerdata[1].value,
									          sf::FloatRect(layerdata[2].parse(0), // @TODO : use stof (and fix that parse method when using them)
			                                                layerdata[3].parse(0),
													        layerdata[4].parse(0),
													        layerdata[5].parse(0)),
			                                  sf::Vector2f(layerdata[6].parse(0),
											               layerdata[7].parse(0))});
		}
	}
}

void Engine::buildSprite(Sprite& spr, const std::string& name)
{
	for (auto& sprdatum : sprdata)
		if (sprdatum.name == name)
			for (auto& layerdatum : sprdatum.layers)
				spr.addSpriteLayer(sprdatum.metaframe, layerdatum.rect, layerdatum.offset);
}

void Engine::buildMeta()
{
	task << "Generating metatexture from imported textures... ";
	meta = std::make_unique<MetaTexture>(texlist);
	texlist.clear();
	std::cout << meta->getTexture().getSize().x << "x" << meta->getTexture().getSize().y << endl;
}

void Engine::setDeltaTarget(int newTarget)
{
	deltatarget = newTarget;
}

float Engine::getDeltaTime()
{
	return deltatime;
}

std::unique_ptr<MetaTexture>& Engine::getMetaTexture() { return meta; }

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

		int wid = conf.getStringValue("fwidth", 0).parse(0), hei = conf.getStringValue("fheight", 0).parse(0);
		task << "Switching to fullscreen mode... ";

		sf::VideoMode mode;
		if (!wid && !hei)
			mode = sf::VideoMode::getDesktopMode();
		else
			mode = sf::VideoMode(wid, hei);

		window.close();
		window.create(mode, "", sf::Style::Fullscreen);
	}
	else
	{
		int wid = conf.getStringValue("wwidth", 0).parse(800), hei = conf.getStringValue("wheight", 0).parse(600);
		window.setSize(sf::Vector2u(wid, hei));
	}

	vbomargin = conf.getStringValue("vbomargin", 0).parse(16);
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
	{
		int zoomlevel = static_cast<int>(view.getSize().x / (preferredWidth * map->getTilesize()));
		view.setSize(static_cast<int>(view.getSize().x / zoomlevel), static_cast<int>(view.getSize().y / zoomlevel));
	}

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