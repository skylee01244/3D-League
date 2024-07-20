#include <array>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Enemy.h"
#include "Headers/Global.h"
#include "Headers/Game.h"
#include "Headers/Player.h"
#include "Headers/ConvertMapSketch.h"

int main()
{
	srand(std::chrono::system_clock::now().time_since_epoch().count()); // Randomising the Seed

	std::chrono::microseconds lag(0);   // make the game framerate-independent

    std::chrono::steady_clock::time_point previous_time;

	Game game;	// main game logic
	sf::Clock clock;

	previous_time = std::chrono::steady_clock::now();

	game.draw();

	while (game.is_open())
	{
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (gbl::SCREEN::FRAME_DURATION <= lag)
		{
			lag -= gbl::SCREEN::FRAME_DURATION;

			game.handle_events();
			float deltaTime = clock.restart().asSeconds();
			game.update(deltaTime);

			if (gbl::SCREEN::FRAME_DURATION > lag)
			{
				game.draw();
			}
		}
	}

    return 0;
}