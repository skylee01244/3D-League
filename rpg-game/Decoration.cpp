#include <array>
#include <chrono>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Global.h"
#include "Headers/SpriteManager.h"
#include "Headers/Animation.h"
#include "Headers/Decoration.h"

Decoration::Decoration(const bool i_is_animation, const std::string& i_sprite_name, SpriteManager& i_sprite_manager, const float i_x, const float i_y) :
	in_the_view(0),
	is_animation(i_is_animation),
	distance(0),
	screen_x(0),
	sprite_name(i_sprite_name),
	position(i_x, i_y),
	sprite_manager(&i_sprite_manager),
	animation(i_sprite_name, i_sprite_manager)
{
	if ("BUSH" == i_sprite_name)
	{
		animation.set_animation_speed(gbl::SPRITES::ANIMATION_SPEED);
	}
}

bool Decoration::operator>(const Decoration& i_decoration) const
{
	return distance > i_decoration.get_distance();
}

bool Decoration::operator<(const Decoration& i_decoration) const
{
	return distance < i_decoration.get_distance();
}

float Decoration::get_distance() const
{
	return distance;
}

int Decoration::get_height() const
{
	return round(gbl::SCREEN::HEIGHT / (distance * tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_VERTICAL))));
}

int Decoration::get_width() const
{
	float sprite_height = sprite_manager->get_sprite_data(sprite_name).texture_box.height;
	float sprite_width = sprite_manager->get_sprite_data(sprite_name).texture_box.width;

	return round(gbl::SCREEN::HEIGHT * sprite_width / (distance * sprite_height * tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL))));
}

int Decoration::get_x() const
{
	return screen_x - round(0.5f * get_width());
}

int Decoration::get_y() const
{
	return round(0.5f * (gbl::SCREEN::HEIGHT - get_height()));
}

void Decoration::draw(const short i_pitch, sf::RenderWindow& i_window)
{
	float sprite_height = sprite_manager->get_sprite_data(sprite_name).texture_box.height;
	float sprite_width = sprite_manager->get_sprite_data(sprite_name).texture_box.width;

	unsigned char shade = 255 * std::clamp<float>(1 - distance / gbl::RAYCASTING::RENDER_DISTANCE, 0, 1);

	in_the_view &= gbl::SCREEN::HEIGHT > i_pitch + get_y() && gbl::SCREEN::WIDTH > get_x() && get_x() > -1 * get_width() && i_pitch + get_y() > -1 * get_height();

	if (0 < shade && 1 == in_the_view)
	{
		if (0 == is_animation)
		{
			sprite_manager->draw_sprite(0, sprite_name, sf::Vector2<short>(get_x(), i_pitch + get_y()), i_window, 0, 0, get_width() / sprite_width, get_height() / sprite_height, sf::Color(shade, shade, shade));
		}
		else
		{
			animation.draw(sf::Vector2<short>(get_x(), i_pitch + get_y()), i_window, 0, 0, get_width() / sprite_width, get_height() / sprite_height, sf::Color(shade, shade, shade));
		}
	}
}

void Decoration::update(const sf::Vector2f& i_player_direction, const sf::Vector2f& i_player_position)
{
	float angle = normalize_radians(atan2(i_player_position.y - position.y, position.x - i_player_position.x));
	float difference = degrees_difference(i_player_direction.x, radians_to_degrees(angle));

	//This makes it so that the difference is between -180 to 180.
	if (degrees_difference(i_player_direction.x, difference + radians_to_degrees(angle)) < degrees_difference(i_player_direction.x, radians_to_degrees(angle) - difference))
	{
		difference *= -1;
	}

	//We're calculating the perpendicular distance, not the Euqalifalistadalidian one.
	distance = abs(i_player_position.y - position.y - tan(degrees_to_radians(i_player_direction.x - 90)) * (position.x - i_player_position.x)) / sqrt(1 + pow(tan(degrees_to_radians(i_player_direction.x - 90)), 2));

	screen_x = round(0.5f * gbl::SCREEN::WIDTH * (1 - tan(degrees_to_radians(difference)) / tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL))));

	in_the_view = 90 > abs(difference);

	if (1 == is_animation)
	{
		animation.update();
	}
}