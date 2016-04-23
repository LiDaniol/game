#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "tilemap.h"
#include "configfile.h"
#include "entity/entitycontext.h"

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

	void importSpritesConfig(const std::string& texkey, const std::string& layerkey);

	void buildMeta();

	void loadConfig(const std::string& conf);
	Config& getConfig();

	void updateView(const sf::View& newView);
	sf::View& getView();

	EntityContext& getContext();

	sf::RenderWindow& getWindow();

private:
		/* Misc */
	Config conf;

	sf::Clock renderclock;
	sf::Clock globalclock;

		/* Windowing */
	sf::RenderWindow window;
	sf::View view;

	bool fullscreen = false; // Redefining this won't change the fullscreen mode.

		/* Rendering */
	Tilemap* map = nullptr;
	MetaTexture* meta = nullptr;

	int vbomargin = 16;

		/* Entities */
	EntityContext ctx;

		/* Resource managment */
	std::vector<sf::Texture> texlist;
	std::vector<SpriteData> sprdata;

	std::vector<std::pair<std::vector<StringValue>, int>> importTextureConfig(const std::string &key); // Returns extra key data + the texture id assigned on the metatexture
};

#endif