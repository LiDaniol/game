#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "tilemap.h"
#include "configfile.h"

class Engine
{
public:
	Engine();
	~Engine(); // @TODO : Use smart pointers to avoid using a destructor

	bool loop();
	void render();

	void addTilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex);
	Tilemap* getTilemap() const;

	void generateTileConfig(const std::string& key);
	MetaTexture* getMetaTexture() const;

	void loadConfig(const std::string& conf);
	Config& getConfig();

	void updateView(const sf::View& newView);
	sf::View& getView();

	sf::RenderWindow& getWindow();

private:
		/* Misc */
	Config conf;

	sf::Clock renderclock;
	sf::Clock globalclock;

		/* Windowing */
	sf::RenderWindow window;
	sf::View view;

		/* Rendering */
	Tilemap* map = nullptr;
	MetaTexture* meta = nullptr;

	int vbomargin = 16;
};

#endif