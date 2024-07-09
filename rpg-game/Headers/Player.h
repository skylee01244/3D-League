#pragma once
#include <array>
#include "Enemy.h"

class Player
{
	float direction_horizontal;
	float direction_vertical;
	float x;
	float y;

	//Using SCREEN_WIDTH here might be wrong since we're skipping some rays when drawing the screen.
	std::array<float, SCREEN_WIDTH> view_rays;

	sf::Sprite map_player_sprite;
	sf::Sprite enemy_sprite;
	sf::Sprite wall_sprite;

	sf::Texture map_player_texture;
	sf::Texture enemy_texture;
	sf::Texture wall_texture;
public:
	Player(float i_x, float i_y);

	void draw_map(sf::RenderWindow& i_window);
	void draw_screen(sf::RenderWindow& i_window, const Enemy& i_enemy);
	void set_position(float i_x, float i_y);
	void update(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, const sf::RenderWindow& i_window);
};