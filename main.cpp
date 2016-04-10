#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"

using namespace std;

int main()
{
	Engine engine;

	while (engine.loop())
	{
		engine.render();
	}

	return 0;
}