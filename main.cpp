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
	e.createSpriteFromEngineData("introship");

	float viewx = 0.f, viewy = 0.f;

	while (engine.loop())
	{
		float dt = engine.getDeltaTime();
		sf::RenderWindow& win = engine.getWindow();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			viewx += dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			viewx -= dt;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			viewy += dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			viewy -= dt;

		sf::View view(sf::FloatRect(0, 0, win.getSize().x, win.getSize().y));
		view.setCenter(viewx, viewy);
		engine.updateView(view);

		engine.render();
	}
}