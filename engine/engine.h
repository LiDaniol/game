#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "map/tilemap.h"
#include "io/configfile.h"
#include "entity/entitycontext.h"

class Engine
{
public:
	Engine();

	void drawEntities(sf::RenderStates states);

	bool loop();
	void render();

	void addTilemap(unsigned int wid, unsigned int hei, unsigned int tilesize, MetaTexture& tex);
	std::unique_ptr<Tilemap>& getTilemap();

	void generateTileConfig(const std::string& key);
	std::unique_ptr<MetaTexture>& getMetaTexture();

	void importSpritesConfig(const std::string& texkey, const std::string& layerkey);
	void buildSprite(Sprite& spr, const std::string& name);

	void buildMeta();

	void setDeltaTarget(int newTarget);
	float getDeltaTime();

	void loadConfig(const std::string& conf);
	Config& getConfig();

	void updateView(const sf::View& newView, int preferredWidth = 50);
	sf::View& getView();

	EntityContext& getContext();

	sf::RenderWindow& getWindow();

private:
		/* Misc */
	Config conf;

	sf::Clock tickTimer;
	sf::Clock titleUpdateTimer;

		/* Windowing */
	sf::RenderWindow window;
	sf::View view;

	bool fullscreen = false; // Redefining this won't change the fullscreen mode.

		/* Map */
	std::unique_ptr<Tilemap> map;
	std::vector<Tile> tileList;

		/* Rendering */
	std::unique_ptr<MetaTexture> meta = nullptr;

	int vbomargin = 16;
	int deltatarget = 60;
	float deltatime = 0;

		/* Entities */
	EntityContext ctx;

		/* Resource managment */
	std::vector<sf::Texture> texlist;
	std::vector<SpriteData> sprdata;

	std::vector<std::pair<std::vector<StringValue>, int>> importTextureConfig(const std::string &key); // Returns extra key data + the texture id assigned on the metatexture
};

#endif