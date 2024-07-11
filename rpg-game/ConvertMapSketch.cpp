#include <array>
#include <chrono>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Headers/Global.h"
#include "Headers/SpriteManager.h"
#include "Headers/Animation.h"
#include "Headers/Decoration.h"
#include "Headers/Player.h"
#include "Headers/Enemy.h"


gbl::MAP::Map<> convert_map_sketch(std::vector<Decoration>& i_decorations, Player& i_player, StevenIzDaBest& i_steven, SpriteManager& i_sprite_manager)
{
	sf::Image map_sketch;
	map_sketch.loadFromFile("Resources/Images/Maps/MapSketch.png");

	gbl::MAP::Map<gbl::MAP::Cell> output_map{};

	for (unsigned char a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned char b = 0; b < gbl::MAP::ROWS; b++)
		{
			sf::Color pixel = map_sketch.getPixel(a, b);

			if (pixel == sf::Color(0, 0, 0))
			{
				output_map[a][b] = gbl::MAP::Cell::Wall;
			}
			else if (pixel == sf::Color(0, 0, 170))
			{
				output_map[a][b] = gbl::MAP::Cell::MugWall;
			}
			else if (pixel == sf::Color(0, 0, 255))
			{
				i_steven.set_position(a, b);
			}
			else if (pixel == sf::Color(109, 0, 0))
			{
				output_map[a][b] = gbl::MAP::Cell::TextWall;
			}
			else if (pixel == sf::Color(182, 0, 0))
			{
				i_decorations.push_back(Decoration(0, "BARREL", i_sprite_manager, a, b));
			}
			else if (pixel == sf::Color(255, 0, 0))
			{
				i_player.set_position(a, b);
			}
			else if (pixel == sf::Color(255, 146, 0))
			{
				i_decorations.push_back(Decoration(1, "FIRE_CAULDRON", i_sprite_manager, a, b));
			}
			else if (pixel == sf::Color(73, 73, 85))
			{
				output_map[a][b] = gbl::MAP::Cell::SkeletonWall;
			}
			else if (pixel == sf::Color(146, 146, 170))
			{
				output_map[a][b] = gbl::MAP::Cell::HelpWall;
			}
			else
			{
				output_map[a][b] = gbl::MAP::Cell::Empty;
			}
		}
	}

	return output_map;
}