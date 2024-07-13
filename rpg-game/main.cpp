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

	std::string fps_text = "FPS: 60"; // This should be 30 as it is currently set to 30 (NEED TO CHANGE TO 60)

	Game game;	// main game logic

	previous_time = std::chrono::steady_clock::now();

	game.draw();

	while (game.is_open())
	{
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		fps_text = "FPS: " + std::to_string(1000000.f / delta_time.count());

		while (gbl::SCREEN::FRAME_DURATION <= lag)
		{
			lag -= gbl::SCREEN::FRAME_DURATION;

			game.handle_events();
			game.update();

			if (gbl::SCREEN::FRAME_DURATION > lag)
			{
				game.draw();
				game.set_title(fps_text);
			}
		}
	}

    return 0;
}