#pragma once
#include <vector>
#include <array>
#include "Stripe.h"
#include "Decoration.h"
#include "Animation.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	bool show_map;
	bool game_start;
	bool game_end;
	bool game_victory;

	std::array<Stripe, gbl::SCREEN::WIDTH> stripes;

	std::vector<Decoration> decorations;

	sf::Event event = sf::Event();

	sf::RenderWindow window;

	sf::VertexArray fov_visualization;

	sf::RectangleShape startButton;
	sf::RectangleShape quitButton;
	sf::RectangleShape restartButton;

	sf::Texture startScreenTexture;
	sf::Sprite startScreenSprite;
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
	void update(float deltaTime);
};