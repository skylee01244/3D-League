#include <array>
#include <chrono>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Headers/Global.h"
#include "Headers/SpriteManager.h"
#include "Headers/Animation.h"
#include "Headers/Decoration.h"
#include "Headers/Player.h"
#include "Headers/Lulu.h"
#include "Headers/Teemo.h"


gbl::MAP::Map<> convert_map_sketch(std::vector<Decoration>& i_decorations, Player& i_player, Lulu& i_lulu, Teemo& i_teemo, SpriteManager& i_sprite_manager)
{
	sf::Image map_sketch;
	map_sketch.loadFromFile("Resources/Images/Maps/MapSketch.png");

	gbl::MAP::Map<gbl::MAP::Cell> output_map{};

	for (unsigned char a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned char b = 0; b < gbl::MAP::ROWS; b++)
		{
			sf::Color pixel = map_sketch.getPixel(a, b);
			//-------------------------Walls-------------------------
			if (pixel == sf::Color(0, 0, 0))					// Black
			{
				output_map[a][b] = gbl::MAP::Cell::Wall;
			}
			else if (pixel == sf::Color(0, 255, 0))				// Lime Green
			{
				output_map[a][b] = gbl::MAP::Cell::FinishWall;
			}
			else if (pixel == sf::Color(0, 0, 25))				// Blueish Black
			{
				output_map[a][b] = gbl::MAP::Cell::TreeWall;
			}
			else if (pixel == sf::Color(0, 0, 50))				// Blue Black
			{
				output_map[a][b] = gbl::MAP::Cell::BushWall;
			}
			else if (pixel == sf::Color(0, 0, 75))				// Blackish Blue
			{
				output_map[a][b] = gbl::MAP::Cell::CaveWall;
			}
			//---------------------Enemies/PLayers-------------------------
			else if (pixel == sf::Color(0, 0, 255))				// Lulu
			{
				i_lulu.set_position(a, b);
			}
			else if (pixel == sf::Color(128, 0, 128))			// Teemo
			{
				i_teemo.set_position(a, b);
			}
			else if (pixel == sf::Color(255, 0, 0))				// Player
			{
				i_player.set_position(a, b);
			}
			//------------------------Decorations-------------------------
			else if (pixel == sf::Color(12, 74, 119))
			{
				i_decorations.push_back(Decoration(0, "TOWER", i_sprite_manager, a, b));
			}
			else if (pixel == sf::Color(28, 53, 16))
			{
				i_decorations.push_back(Decoration(1, "BUSH", i_sprite_manager, a, b));
			}
			//-------------------------Empty-------------------------
			else
			{
				output_map[a][b] = gbl::MAP::Cell::Empty;
			}
		}
	}

	return output_map;
}