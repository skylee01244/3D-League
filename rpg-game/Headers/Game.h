#pragma once
#include <vector>
#include <array>
#include "Stripe.h"
#include "Decoration.h"
#include "Animation.h"
#include "Player.h"

class Game
{
	bool show_map;

	float hand_offset;

	std::array<Stripe, gbl::SCREEN::WIDTH> stripes;

	std::vector<Decoration> decorations;

	sf::Event event = sf::Event();

	sf::RenderWindow window;

	sf::VertexArray fov_visualization;

	SpriteManager sprite_manager;

	Player player;

	Enemy enemy;

	gbl::MAP::Map<> map;

public:
	Game();

	bool is_open() const;

	void calculate_fov_visualization();
	void draw();
	void draw_map();
	void handle_events();
	void raycast();
	void set_title(const std::string& i_title);
	void update();
};