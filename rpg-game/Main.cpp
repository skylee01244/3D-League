#include <array>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Enemy.h"
#include "Headers/Teemo.h"
#include "Headers/Global.h"
#include "Headers/Game.h"
#include "Headers/Player.h"
#include "Headers/ConvertMapSketch.h"

int main()
{

	Game game;
	sf::Clock clock;

	game.setFrameRateLimit(60);

	game.draw();

	while (game.is_open())
	{
		game.handle_events();

		float deltaTime = clock.restart().asSeconds();
		game.update(deltaTime);
		game.draw();
	}
    return 0;
}