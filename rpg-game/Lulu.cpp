#include <array>
#include <chrono>
#include <unordered_map>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Global.h"
#include "Headers/Astar.h"
#include "Headers/SpriteManager.h"
#include "Headers/MapCollision.h"
#include "Headers/Lulu.h"

Lulu::Lulu(SpriteManager& i_sprite_manager, float i_x, float i_y) :
	in_view(false),
	caught(false),
	direction(0.0f),
	distance(0.0f),
	screen_x(0),
	current_frame(0),
	position(i_x, i_y),
	sprite_manager(&i_sprite_manager),
	astar_path_length(0),
	next_cell(position),
	astar_map({}),
	astar_f_scores({}),
	astar_g_scores({}),
	astar_h_scores({})
{
}

bool Lulu::get_caught() const
{
	return caught;
}

float Lulu::get_direction() const
{
	return direction;
}

float Lulu::get_distance() const
{
	return distance;
}

int Lulu::get_height() const
{
	float projectionFactor = distance * std::tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_VERTICAL));
	return static_cast<int>(std::round(gbl::SCREEN::HEIGHT / projectionFactor));
}

int Lulu::get_width() const
{
	float sprite_height = sprite_manager->get_sprite_data("LULU").texture_box.height;
	float sprite_width = sprite_manager->get_sprite_data("LULU").texture_box.width;

	float projectionFactor = distance * sprite_height * std::tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL));
	return static_cast<int>(std::round(gbl::SCREEN::HEIGHT * sprite_width / projectionFactor));
}

int Lulu::get_x() const
{
	return screen_x - static_cast<int>(std::round(0.5f * get_width()));
}

int Lulu::get_y() const
{
	return static_cast<int>(std::round(0.5f * (gbl::SCREEN::HEIGHT - get_height())));
}

void Lulu::draw(const short i_pitch, sf::RenderWindow& i_window)
{
	float sprite_height = sprite_manager->get_sprite_data("LULU").texture_box.height;
	float sprite_width = sprite_manager->get_sprite_data("LULU").texture_box.width;

	unsigned char shade = static_cast<unsigned char>(255 * std::clamp(1.f - distance / gbl::RAYCASTING::RENDER_DISTANCE, 0.f, 1.f));

	in_view &= gbl::SCREEN::HEIGHT > i_pitch + get_y() && gbl::SCREEN::WIDTH > get_x() && get_x() > -1 * get_width() && i_pitch + get_y() > -1 * get_height();

	if (shade > 0 && in_view)
	{
		sprite_manager->draw_sprite(current_frame, "LULU", sf::Vector2<short>(get_x(), i_pitch + get_y()), i_window, 0, 0, get_width() / sprite_width, get_height() / sprite_height, sf::Color(shade, shade, shade));
	}
}

void Lulu::fill_map(const gbl::MAP::Map<>& i_map)
{
	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++) {
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			if (gbl::MAP::Cell::Empty != i_map[a][b])
			{
				astar_map[a][b] = gbl::MAP::PathCell::Wall;
			}
			else
			{
				astar_map[a][b] = gbl::MAP::PathCell::Empty;
			}
		}
	}
}

void Lulu::set_position(const float i_x, const float i_y)
{
	position.x = i_x;
	position.y = i_y;

	next_cell.x = position.x;
	next_cell.y = position.y;
}

void Lulu::update(const sf::RenderWindow& i_window, const sf::Vector2f& i_player_direction, const sf::Vector2f& i_player_position, const gbl::MAP::Map<>& i_map, float deltaTime)
{
	if (i_window.hasFocus())
	{
		// angle between enemy and player
		float angle = normalize_radians(atan2(i_player_position.y - position.y, position.x - i_player_position.x));
		float difference = degrees_difference(i_player_direction.x, radians_to_degrees(angle));
		float frame_angle = 360.f / sprite_manager->get_sprite_data("LULU").total_frames;
		float shifted_direction;
		float speed = 0;
		float step_x = 0;
		float step_y = 0;

		sf::Vector2<unsigned short> finish_position(round(i_player_position.x), round(i_player_position.y));
		sf::Vector2<unsigned short> start_position(round(position.x), round(position.y));

		if (finish_position != start_position)
		{
			astar_reset(astar_path_length, astar_previous_cell, astar_path_vector, astar_f_scores, astar_g_scores, astar_h_scores, finish_position, start_position, astar_map);
			astar_search(astar_path_length, astar_previous_cell, astar_path_vector, astar_f_scores, astar_g_scores, astar_h_scores, next_cell, finish_position, start_position, astar_map);

			direction = radians_to_degrees(atan2(position.y - next_cell.y, next_cell.x - position.x));
			speed = gbl::ENEMY::MOVEMENT_SPEED;
		}

		if (1 > std::sqrt(pow(position.x - i_player_position.x, 2) + pow(position.y - i_player_position.y, 2)))
		{
			caught = true;
		}

		// Compute step increments towards the next cell along x and y axes.
		if (next_cell.x < position.x)
		{
			step_x = std::max(-speed * deltaTime, next_cell.x - position.x);
		}
		else if (next_cell.x > position.x)
		{
			step_x = std::min(speed * deltaTime, next_cell.x - position.x);
		}
		if (next_cell.y < position.y)
		{
			step_y = std::max(-speed * deltaTime, next_cell.y - position.y);
		}
		else if (next_cell.y > position.y)
		{
			step_y = std::min(speed * deltaTime, next_cell.y - position.y);
		}

		// Update position based on collision detection.
		if (map_collision(step_x + position.x, step_y + position.y, i_map) == false)
		{
			position.x += step_x;
			position.y += step_y;
		}
		else if (map_collision(step_x + position.x, position.y, i_map) == false)
		{
			position.x += step_x;
			position.y = round(position.y);
		}
		else if (map_collision(position.x, step_y + position.y, i_map) == false)
		{
			position.x = round(position.x);
			position.y += step_y;
		}
		else
		{
			position.x = round(position.x);
			position.y = round(position.y);
		}

		if (degrees_difference(i_player_direction.x, difference + radians_to_degrees(angle)) < degrees_difference(i_player_direction.x, radians_to_degrees(angle) - difference))
		{
			difference *= -1;
		}

		shifted_direction = normalize_degrees(90 + normalize_degrees(direction + 0.5f * frame_angle) - difference - i_player_direction.x);

		//perpendicular distance 
		distance = std::abs(i_player_position.y - position.y - tan(degrees_to_radians(i_player_direction.x - 90)) * (position.x - i_player_position.x)) / std::sqrt(1 + pow(tan(degrees_to_radians(i_player_direction.x - 90)), 2));

		screen_x = round(0.5f * gbl::SCREEN::WIDTH * (1 - std::tan(degrees_to_radians(difference)) / std::tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL))));

		in_view = std::abs(difference) < 90;

		current_frame = static_cast<int>(std::floor(shifted_direction / frame_angle));
	}
}

sf::Vector2f Lulu::get_position() const
{
	return position;
}