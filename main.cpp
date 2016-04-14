#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"

using namespace std;

int main()
{
	Engine engine;
	engine.loadConfig("main.conf");
	engine.generateTextureConfig("tileset");
	engine.addTilemap(800, 800, 8, *engine.getMetaTexture());

	while (engine.loop())
	{
		sf::RenderWindow& win = engine.getWindow();
		sf::Vector2i mousepos = sf::Mouse::getPosition(win);
		sf::View view(sf::FloatRect(mousepos.x, mousepos.y, win.getSize().x, win.getSize().y));
		engine.updateView(view);

		engine.render();
	}
}