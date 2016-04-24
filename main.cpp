#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"
#include "engine/render/sprite.h"

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

	float viewx = 0.f, viewy = 0.f;

	while (engine.loop())
	{
		sf::RenderWindow& win = engine.getWindow();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			++viewx;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			--viewx;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			++viewy;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			--viewy;

		sf::View view(sf::FloatRect(viewx, viewy, win.getSize().x, win.getSize().y));
		engine.updateView(view);

		engine.render();
	}
}