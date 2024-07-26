#pragma once
#include <vector>
#include <array>
#include "Stripe.h"
#include "Decoration.h"
#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include "Teemo.h"
#include "GameState.h"

class Game
{
private:
	void initialise();
	bool show_map;

	std::array<Stripe, gbl::SCREEN::WIDTH> stripes;

	std::vector<Decoration> decorations;

	sf::Event event = sf::Event();

	sf::RenderWindow window;

	sf::VertexArray fov_visualization;

	sf::RectangleShape startButton, quitButton, restartButton;

	sf::Texture startScreenTexture;
	sf::Sprite startScreenSprite;
	SpriteManager sprite_manager;

	Player player;
	Enemy enemy1;
	Teemo teemo;
	gbl::MAP::Map<> map;

public:
	GameState game_state;

public:
	Game();
	void restart();
	bool is_open() const;
	void calculate_fov_visualization();
	void draw();
	void draw_start_screen();
	void draw_end_screen();
	void draw_victory_screen();
	void draw_gameplay();
	void draw_map();
	void handle_events();
	void raycast();
	void update(float deltaTime);
};