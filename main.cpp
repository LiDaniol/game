#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"

using namespace std;

int main()
{
	Engine engine;
	engine.loadConfig("main.conf");
	engine.generateTextureConfig("tileset");
	engine.addTilemap(80, 50, 8, *engine.getMetaTexture());

	while (engine.loop())
	{
		engine.render();
	}

	return 0;
}