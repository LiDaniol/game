#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"
#include "engine/entity/sprite.h"

using namespace std;

int main()
{
	Engine engine;

	engine.loadConfig("main.conf");

	// Import resources
	engine.generateTileConfig("tile"); // Import tiles from config
	engine.importSpritesConfig("sprite", "spritelayer");
	engine.buildMeta();

	engine.addTilemap(500, 500, 8, *engine.getMetaTexture());

	Entity& e = engine.getContext().addEntity();
	e.setPosition(sf::Vector2f(3.f, 3.f));
	Sprite* spr = e.createSprite();
	spr->addSpriteLayer(4, sf::FloatRect(0, 0, 300, 100)); // random shizzle for now

	while (engine.loop())
	{
		/*sf::RenderWindow& win = engine.getWindow();
		sf::Vector2i mousepos = sf::Mouse::getPosition(win);
		sf::View view(sf::FloatRect(mousepos.x, mousepos.y, win.getSize().x, win.getSize().y));*/
		//engine.updateView(view);

		engine.render();
	}
}