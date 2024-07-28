#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace gbl
{
	struct SpriteData
	{
		unsigned short total_frames;

		std::string image_location;
		std::string name;

		sf::Rect<unsigned short> texture_box;

		sf::Sprite* sprite;

		sf::Vector2<short> origin;
	};

	namespace MAP
	{
		constexpr unsigned char CELL_SIZE = 3;
		constexpr unsigned char COLUMNS = 64;
		constexpr unsigned char ROWS = 64;

		//map.
		enum class Cell
		{
			Empty,
			Wall,
			TreeWall,
			FinishWall,
			BushWall,
			CaveWall
		};

		//A* pathfinding.
		enum class PathCell
		{
			Empty,
			Invalid,
			Visited,
			Wall
		};

		template <typename value_type = Cell>
		using Map = std::array<std::array<value_type, ROWS>, COLUMNS>;
	}

	namespace PLAYER
	{
		constexpr float MOVEMENT_SPEED = 3.5f;
	}

	namespace RAYCASTING
	{
		constexpr float FOV_HORIZONTAL = 90;
		constexpr float FOV_VERTICAL = 90;
		constexpr float MAX_VERTICAL_DIRECTION = 60;
		constexpr float PI = 3.141592653589793116f;
		constexpr float RENDER_DISTANCE = 8;
	}

	namespace SCREEN
	{
		constexpr unsigned char RESIZE = 2;

		constexpr unsigned short HEIGHT = 360;
		constexpr unsigned short WIDTH = 640;
	}

	namespace SPRITES
	{
		constexpr float ANIMATION_SPEED = 0.20f;
	}


	namespace ENEMY
	{
		constexpr float MAX_MOVEMENT_DISTANCE = 32.f;
		constexpr float MAX_MOVEMENT_SPEED = 2.9f;
		constexpr float MIN_MOVEMENT_DISTANCE = 4.f;
		constexpr float MIN_MOVEMENT_SPEED = 2.5f;
	}

	template <typename value_type = unsigned short>
	using Position = std::pair<value_type, value_type>;
}