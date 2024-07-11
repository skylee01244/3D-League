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

	Game game;

	previous_time = std::chrono::steady_clock::now();

	game.draw();

    //sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;
    //sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "2D game", sf::Style::Default);
    //window.setMouseCursorVisible(100);  // 0 to hide Cursor
    //window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));

	/*while (1 == window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) { window.close(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) { draw_map = 1 - draw_map; }
	}*/

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