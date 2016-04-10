#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"

using namespace std;

int main()
{
	Engine engine;
	engine.loadConfig("main.conf");

	while (engine.loop())
	{
		engine.render();
	}

	return 0;
}