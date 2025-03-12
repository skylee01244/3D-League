#include <array>
#include <chrono>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Headers/Global.h"
#include "Headers/SpriteManager.h"
#include "Headers/Animation.h"

Animation::Animation(const std::string& i_sprite_name, SpriteManager& i_sprite_manager, const bool i_ping_pong, const float i_animation_speed, const float i_current_frame) :
	ping_pong(i_ping_pong),
	sprite_data(&i_sprite_manager.get_sprite_data(i_sprite_name)),
	sprite_manager(&i_sprite_manager)
{
	// Calculte total frames (if pingpong mode, double the sequence)
	total_frames = (!ping_pong) ? sprite_data->total_frames : 2 * (sprite_data->total_frames - 1);

	set_animation_speed(i_animation_speed);
	set_current_frame(i_current_frame);
}

bool Animation::update(const char i_animation_end)
{
	const float nextFrame = current_frame + animation_speed;
	bool leftBoundaryReached = false;
	bool rightBoundaryReached = false;

	if (!ping_pong)
	{
		leftBoundaryReached = (nextFrame < 0);
		rightBoundaryReached = (nextFrame >= total_frames);
	}
	else
	{
		leftBoundaryReached = 0 > nextFrame || total_frames <= nextFrame;
		rightBoundaryReached = current_frame < sprite_data->total_frames && sprite_data->total_frames <= nextFrame;
		//  animation direction switches.
		if (!rightBoundaryReached)
		{
			rightBoundaryReached = current_frame >= sprite_data->total_frames && sprite_data->total_frames > nextFrame;
		}
	}

	current_frame = std::fmod(animation_speed + current_frame + total_frames, total_frames);

	switch (i_animation_end)
	{
	case -1:
	{
		return leftBoundaryReached;
	}
	case 0:
	{
		return leftBoundaryReached || rightBoundaryReached;
	}
	case 1:
	{
		return rightBoundaryReached;
	}
	default:
	{
		return false;
	}
	}
}

float Animation::get_animation_speed() const
{
	return animation_speed;
}

float Animation::get_current_frame() const
{
	return current_frame;
}

void Animation::draw(const sf::Vector2<short>& i_position, sf::RenderWindow& i_window, const bool i_mirror_horizontal, const bool i_mirror_vertical, const float i_scale_x, const float i_scale_y, const sf::Color& i_color, const sf::Rect<unsigned short>& i_texture_box) const
{
	unsigned short frame = static_cast<unsigned short>(std::floor(current_frame));

	if (ping_pong && frame >= sprite_data->total_frames) {
		frame = sprite_data->total_frames - 1 - (frame - sprite_data->total_frames);
	}

	sprite_manager->draw_sprite(frame, sprite_data->name, i_position, i_window, i_mirror_horizontal, i_mirror_vertical, i_scale_x, i_scale_y, i_color, i_texture_box);
}

void Animation::set_animation_speed(const float i_animation_speed)
{
	animation_speed = std::fmod(i_animation_speed, total_frames);
}

void Animation::set_current_frame(const float i_current_frame)
{
	current_frame = fmod(total_frames + fmod(i_current_frame, total_frames), total_frames);
}