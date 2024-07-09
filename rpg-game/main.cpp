#include <SFML/Graphics.hpp>    
#include <iostream>

#include "Headers/Angles.h"
#include "Headers/Enemy.h"
#include "Headers/Global.h"
#include "Headers/Player.h"
#include "Headers/ConvertSketch.h"

int main()
{
    bool draw_map = 1;
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

    std::chrono::microseconds lag(0);   // make the game framerate-independent

    std::chrono::steady_clock::time_point previous_time;

    sf::Event event;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "2D game", sf::Style::Default);
    window.setMouseCursorVisible(100);  // 0 to hide Cursor
    window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
    
    sf::Sprite map_grid_cell_sprite;
    sf::Sprite map_wall_sprite;

    sf::Texture map_grid_cell_texture;
    map_grid_cell_texture.loadFromFile("Resources/Images/MapGridCell.png");

    sf::Texture map_wall_texture;
    map_wall_texture.loadFromFile("Resources/Images/MapWall" + std::to_string(MAP_CELL_SIZE) + ".png");

    Player player(0, 0);
    Enemy enemy(0, 0);

    map = convert_sketch(player, enemy);

    map_grid_cell_sprite.setTexture(map_grid_cell_texture);
    map_grid_cell_sprite.setTextureRect(sf::IntRect(0, 0, MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE));
    map_wall_sprite.setTexture(map_wall_texture);

    previous_time = std::chrono::steady_clock::now();

    sf::Clock clock;

    while (window.isOpen()) 
	{
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) { window.close(); }
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) { draw_map = 1 - draw_map; }
			}

			player.update(map, window);

			enemy.update(map, window);

			if (FRAME_DURATION > lag)
			{
				window.clear(sf::Color(73, 255, 255));		// Colour the sky

				player.draw_screen(window, enemy);

				if (1 == draw_map)
				{
					for (unsigned short a = 0; a < ceil(MAP_CELL_SIZE * MAP_WIDTH / static_cast<float>(MAP_GRID_CELL_SIZE)); a++)
					{
						for (unsigned short b = 0; b < ceil(MAP_CELL_SIZE * MAP_HEIGHT / static_cast<float>(MAP_GRID_CELL_SIZE)); b++)
						{
							map_grid_cell_sprite.setPosition(static_cast<float>(MAP_GRID_CELL_SIZE * a), static_cast<float>(MAP_GRID_CELL_SIZE * b));

							window.draw(map_grid_cell_sprite);
						}
					}

					for (unsigned short a = 0; a < MAP_WIDTH; a++)
					{
						for (unsigned short b = 0; b < MAP_HEIGHT; b++)
						{
							if (Cell::Wall == map[a][b])
							{
								map_wall_sprite.setPosition(static_cast<float>(MAP_CELL_SIZE * a), static_cast<float>(MAP_CELL_SIZE * b));

								window.draw(map_wall_sprite);
							}
						}
					}
					player.draw_map(window);

					enemy.draw_map(window);
				}
				window.display();
			}
		}
    }

    return 0;
}