#include <array>
#include <chrono>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <limits>
#include <iostream>

#include "Headers/Global.h"
#include "Headers/AngleFunctions.h"
#include "Headers/SpriteManager.h"
#include "Headers/Animation.h"
#include "Headers/Stripe.h"
#include "Headers/Decoration.h"
#include "Headers/Player.h"
#include "Headers/Lulu.h"
#include "Headers/ConvertMapSketch.h"
#include "Headers/Game.h"
#include "Headers/Teemo.h"
#include "Headers/GameState.h"


void Game::setFrameRateLimit(unsigned int limit)
{
	window.setFramerateLimit(limit);
}

Game::Game() :
	show_map(0),
	window(sf::VideoMode(gbl::SCREEN::RESIZE* gbl::SCREEN::WIDTH, gbl::SCREEN::RESIZE* gbl::SCREEN::HEIGHT), "Raycasting", sf::Style::Default),
	fov_visualization(sf::TriangleFan, 1 + gbl::SCREEN::WIDTH),
	lulu(sprite_manager),
	teemo(sprite_manager),
	game_state(GameState::GAME_START)
{
	initialise();
}

void Game::initialise() {
	game_state = GameState::GAME_START;
	show_map = false;

	window.setMouseCursorVisible(1);
	window.setView(sf::View(sf::FloatRect(0, 0, gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT)));

	player = Player();
	lulu = Lulu(sprite_manager);
	teemo = Teemo(sprite_manager);

	map = convert_map_sketch(decorations, player, lulu, teemo, sprite_manager);
	lulu.fill_map(map);
	teemo.fill_map(map);

	for (Stripe& stripe : stripes) {
		stripe.set_sprite_manager(sprite_manager);
	}

	startButton.setSize(sf::Vector2f(85, 125));
	startButton.setPosition(545, 20);

	quitButton.setSize(sf::Vector2f(110, 60));
	quitButton.setPosition(180, 235);

	restartButton.setSize(sf::Vector2f(110, 60));
	restartButton.setPosition(350, 235);
}

void Game::restart()
{
	initialise();
}

bool Game::is_open() const
{
	return window.isOpen();
}

void Game::updateFOV() {
	// Calculate the start position based on player position
	sf::Vector2f startPosition(
		gbl::MAP::CELL_SIZE * (0.5f + player.get_position().x),
		gbl::MAP::CELL_SIZE * (0.5f + player.get_position().y)
	);

	fov_visualization[0].position = startPosition;

	// Update FOV visualization for each stripe
	for (unsigned short i = 0; i < gbl::SCREEN::WIDTH; ++i) {
		float distance = stripes[i].get_true_distance();
		float angle = stripes[i].get_angle();

		fov_visualization[1 + i].position = sf::Vector2f(
			startPosition.x + gbl::MAP::CELL_SIZE * distance * cos(angle),
			startPosition.y - gbl::MAP::CELL_SIZE * distance * sin(angle)
		);
	}
}

void Game::draw() {
	switch (game_state) {
	case GameState::GAME_START:
		draw_start_screen();
		break;
	case GameState::GAME_PLAYING:
		//draw_gameplay();
		renderGameplay();
		break;
	case GameState::GAME_END:
		draw_end_screen();
		break;
	case GameState::GAME_VICTORY:
		draw_victory_screen();
		break;
	}
	window.display();
}

void Game::draw_start_screen() {
	sf::Vector2<short> position(0, 0);
	sf::Color color = sf::Color::White;
	auto& spriteData = sprite_manager.get_sprite_data("StartScreen");
	sf::Rect<unsigned short> textureBox = spriteData.texture_box;
	sprite_manager.draw_sprite(0, "StartScreen", position, window, false, false, 1.0f, 1.0f, color, textureBox);

	// Start button
	auto& startButtonSpriteData = sprite_manager.get_sprite_data("StartButton");
	sf::Vector2<short> startButtonPosition(545, 20);
	sf::Rect<unsigned short> startButtonTextureBox = startButtonSpriteData.texture_box;
	sprite_manager.draw_sprite(0, "StartButton", startButtonPosition, window, false, false, 1.0f, 1.0f, color, startButtonTextureBox);
}

void Game::draw_end_screen() {
	sf::Vector2<short> position(0, 0);
	sf::Color color = sf::Color::White;
	auto& spriteData = sprite_manager.get_sprite_data("EndScreen");
	sf::Rect<unsigned short> textureBox = spriteData.texture_box;
	sprite_manager.draw_sprite(0, "EndScreen", position, window, false, false, 1.0f, 1.0f, color, textureBox);

	// Quit button
	auto& quitButtonSpriteData = sprite_manager.get_sprite_data("QuitButton");
	sf::Vector2<short> quitButtonPosition(180, 235);
	sf::Rect<unsigned short> quitButtonTextureBox = quitButtonSpriteData.texture_box;
	sprite_manager.draw_sprite(0, "QuitButton", quitButtonPosition, window, false, false, 1.0f, 1.0f, color, quitButtonTextureBox);

	// Restart button
	auto& restartButtonSpriteData = sprite_manager.get_sprite_data("PlayButton");
	sf::Vector2<short> restartButtonPosition(350, 235);
	sf::Rect<unsigned short> restartButtonTextureBox = restartButtonSpriteData.texture_box;
	sprite_manager.draw_sprite(0, "PlayButton", restartButtonPosition, window, false, false, 1.0f, 1.0f, color, restartButtonTextureBox);
}

void Game::draw_victory_screen() {
	sf::Vector2<short> position(0, 0);
	sf::Color color = sf::Color::White;
	auto& spriteData = sprite_manager.get_sprite_data("VictoryScreen");
	sf::Rect<unsigned short> textureBox = spriteData.texture_box;
	sprite_manager.draw_sprite(0, "VictoryScreen", position, window, false, false, 1.0f, 1.0f, color, textureBox);

	// Quit button
	auto& quitButtonSpriteData = sprite_manager.get_sprite_data("QuitButton");
	sf::Vector2<short> quitButtonPosition(180, 235);
	sf::Rect<unsigned short> quitButtonTextureBox = quitButtonSpriteData.texture_box;
	sprite_manager.draw_sprite(0, "QuitButton", quitButtonPosition, window, false, false, 1.0f, 1.0f, color, quitButtonTextureBox);

	// Restart button
	auto& restartButtonSpriteData = sprite_manager.get_sprite_data("PlayButton");
	sf::Vector2<short> restartButtonPosition(350, 235);
	sf::Rect<unsigned short> restartButtonTextureBox = restartButtonSpriteData.texture_box;
	sprite_manager.draw_sprite(0, "PlayButton", restartButtonPosition, window, false, false, 1.0f, 1.0f, color, restartButtonTextureBox);
}

void Game::renderGameplay() {
	if (lulu.get_caught() || teemo.get_caught()) {
		game_state = GameState::GAME_END;
		return;
	}

	bool isLuluDrawn = false;
	bool isTeemoDrawn = false;

	float startStripeX = -tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL));
	float endStripeX = tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL)) * (1 - 2.f / gbl::SCREEN::WIDTH);
	float verticalFovRatio = tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_VERTICAL));
	short pitch = round(0.5f * gbl::SCREEN::HEIGHT * tan(degrees_to_radians(player.get_direction().y)));
	unsigned short floorStartY = std::clamp<float>(pitch + 0.5f * gbl::SCREEN::HEIGHT, 0, gbl::SCREEN::HEIGHT);

	gbl::SpriteData floorSpriteData = sprite_manager.get_sprite_data("FLOOR");
	sf::Image floorImage, floorBufferImage;
	floorImage.loadFromFile(floorSpriteData.image_location);
	floorBufferImage.create(gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT - floorStartY);

	sf::Sprite floorSprite;
	floorSprite.setPosition(0, floorStartY);
	sf::Texture floorTexture;

	float playerDirection = degrees_to_radians(player.get_direction().x);
	float playerDirectionOffset = degrees_to_radians(player.get_direction().x - 90);
	float rayDirStartX = cos(playerDirection) + startStripeX * cos(playerDirectionOffset);
	float rayDirStartY = -sin(playerDirection) - startStripeX * sin(playerDirectionOffset);
	float rayDirEndX = cos(playerDirection) + endStripeX * cos(playerDirectionOffset);
	float rayDirEndY = -sin(playerDirection) - endStripeX * sin(playerDirectionOffset);

	window.clear();

	for (unsigned short y = floorStartY; y < gbl::SCREEN::HEIGHT; ++y) {
		short rowY = y - pitch - 0.5f * gbl::SCREEN::HEIGHT;
		float rowDistance = (rowY == 0) ? std::numeric_limits<float>::max() : 0.5f * gbl::SCREEN::HEIGHT / (rowY * verticalFovRatio);
		unsigned char shade = 255 * std::clamp<float>(1 - rowDistance / gbl::RAYCASTING::RENDER_DISTANCE, 0, 1);

		if (shade > 0) {
			float floorStepX = rowDistance * (rayDirEndX - rayDirStartX) / gbl::SCREEN::WIDTH;
			float floorStepY = rowDistance * (rayDirEndY - rayDirStartY) / gbl::SCREEN::WIDTH;
			float floorX = 0.5f + player.get_position().x + rayDirStartX * rowDistance;
			float floorY = 0.5f + player.get_position().y + rayDirStartY * rowDistance;

			for (unsigned short x = 0; x < gbl::SCREEN::WIDTH; ++x) {
				unsigned int textureX = static_cast<unsigned int>(floorSpriteData.texture_box.width * (5 + floorX - floor(floorX)));
				unsigned int textureY = static_cast<unsigned int>(floorSpriteData.texture_box.height * (floorY - floor(floorY)));

				// check bounds of the image
				textureX = std::clamp(textureX, 0u, floorImage.getSize().x - 1);
				textureY = std::clamp(textureY, 0u, floorImage.getSize().y - 1);

				sf::Color pixelColor = floorImage.getPixel(textureX, textureY);
				floorX += floorStepX;
				floorY += floorStepY;
				pixelColor *= sf::Color(shade, shade, shade);
				floorBufferImage.setPixel(x, y - floorStartY, pixelColor);
			}
		}
	}

	floorTexture.loadFromImage(floorBufferImage);
	floorSprite.setTexture(floorTexture);
	window.draw(floorSprite);

	updateFOV();

	std::sort(decorations.begin(), decorations.end(), std::greater<>());
	std::sort(stripes.begin(), stripes.end(), std::greater<>());

	unsigned short decorationIndex = 0;

	auto drawCharacter = [&](auto& character, bool& isDrawn) {
		if (!isDrawn && decorationIndex < decorations.size() && character.get_distance() > decorations[decorationIndex].get_distance()) {
			isDrawn = true;
			character.draw(pitch, window);
		}
		};

	for (Stripe& stripe : stripes) {
		while (decorationIndex < decorations.size() && stripe.get_distance() < decorations[decorationIndex].get_distance()) {
			drawCharacter(lulu, isLuluDrawn);
			drawCharacter(teemo, isTeemoDrawn);
			decorations[decorationIndex++].draw(pitch, window);
		}

		drawCharacter(lulu, isLuluDrawn);
		drawCharacter(teemo, isTeemoDrawn);
		stripe.draw(pitch, window);
	}

	for (unsigned short i = decorationIndex; i < decorations.size(); ++i) {
		drawCharacter(lulu, isLuluDrawn);
		drawCharacter(teemo, isTeemoDrawn);
		decorations[i].draw(pitch, window);
	}

	if (!isLuluDrawn) lulu.draw(pitch, window);
	if (!isTeemoDrawn) teemo.draw(pitch, window);
	if (show_map) draw_map();
}

void Game::draw_map()
{
	float frame_angle = 360.f / sprite_manager.get_sprite_data("MAP_PLAYER").total_frames;
	float shifted_direction = normalize_degrees(player.get_direction().x + 0.5f * frame_angle);
	float enemy1_shifted_direction = normalize_degrees(lulu.get_direction() + 0.5f * frame_angle);
	float enemy2_shifted_direction = normalize_degrees(teemo.get_direction() + 0.5f * frame_angle);

	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			switch (map[a][b])
			{
			case gbl::MAP::Cell::Empty:
			{
				sprite_manager.draw_sprite(0, "MAP_CELL", sf::Vector2<short>(gbl::MAP::CELL_SIZE * a, gbl::MAP::CELL_SIZE * b), window);

				break;
			}
			default:
			{
				sprite_manager.draw_sprite(0, "MAP_WALL", sf::Vector2<short>(gbl::MAP::CELL_SIZE * a, gbl::MAP::CELL_SIZE * b), window);
			}
			}
		}
	}

	window.draw(fov_visualization);

	sprite_manager.draw_sprite(floor(enemy1_shifted_direction / frame_angle), "MAP_STEVEN", sf::Vector2<short>(round(gbl::MAP::CELL_SIZE * lulu.get_position().x), round(gbl::MAP::CELL_SIZE * lulu.get_position().y)), window);
	sprite_manager.draw_sprite(floor(enemy2_shifted_direction / frame_angle), "MAP_STEVEN", sf::Vector2<short>(round(gbl::MAP::CELL_SIZE * teemo.get_position().x), round(gbl::MAP::CELL_SIZE * teemo.get_position().y)), window);
	sprite_manager.draw_sprite(floor(shifted_direction / frame_angle), "MAP_PLAYER", sf::Vector2<short>(round(gbl::MAP::CELL_SIZE * player.get_position().x), round(gbl::MAP::CELL_SIZE * player.get_position().y)), window);
}

void Game::handle_events()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					case sf::Keyboard::M:
					{
						show_map = 1 - show_map;
						break;
					}
					default:
						break;
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if ((event.mouseButton.button == sf::Mouse::Left) && (game_state == GameState::GAME_START))
				{
					if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						game_state = GameState::GAME_PLAYING;
						window.setMouseCursorVisible(0);
					}
				}
				if ((event.mouseButton.button == sf::Mouse::Left) && ((game_state == GameState::GAME_END || game_state == GameState::GAME_VICTORY)))
				{
					if (quitButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						window.close();
					}
					if (restartButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
					{
						window.setMouseCursorVisible(0);
						restart();
					}
				}
				break;
			}
			default:
				break;
		}	
		player.handle_movement_events(event, map);
	}
}

void Game::raycast()
{
	float ray_start_x = 0.5f + player.get_position().x;
	float ray_start_y = 0.5f + player.get_position().y;

	for (unsigned short a = 0; a < gbl::SCREEN::WIDTH; a++)
	{
		char cell_step_x = 0;
		char cell_step_y = 0;

		//Current stripe's x-coordinate relative to the direction of the player.
		float current_stripe_x = tan(degrees_to_radians(0.5f * gbl::RAYCASTING::FOV_HORIZONTAL)) * (2 * a / static_cast<float>(gbl::SCREEN::WIDTH) - 1);
		//The angle between the player's direction and the direction to the current stripe.
		float ray_angle;
		//Ray's direction represented in coordinates (or distances. I don't know how to say it correctly).
		//I wanna say "vector" but I know some people will say "ACKULUQIDARTUALLY!!!!! A vector has a DIRECTION and a MAGNITUDE!" so I won't.
		float ray_direction_x = cos(degrees_to_radians(player.get_direction().x)) + current_stripe_x * cos(degrees_to_radians(player.get_direction().x - 90));
		float ray_direction_y = -sin(degrees_to_radians(player.get_direction().x)) - current_stripe_x * sin(degrees_to_radians(player.get_direction().x - 90));
		float side_x;
		//This ray checks for horizontal collisions.
		float x_ray_length = 0;
		float x_ray_unit_length = (0 == ray_direction_x) ? std::numeric_limits<float>::max() : std::abs(1 / ray_direction_x);
		//This ray checks for vertical collisions.
		float y_ray_length = 0;
		float y_ray_unit_length = (0 == ray_direction_y) ? std::numeric_limits<float>::max() : std::abs(1 / ray_direction_y);

		unsigned char current_cell_x = floor(ray_start_x);
		unsigned char current_cell_y = floor(ray_start_y);
		//The side of the wall.
		//When you're looking at the map from above.
		//0 - Left side.
		//1 - Top side.
		//2 - Right side.
		//3 - Bottom side.
		unsigned char side = 0;

		gbl::MAP::Cell collision_cell;

		//In order for the algorithm to work, the ray must start at the cell borders.
		//So if the starting position of the ray is not a cell border (which is very likely), we'll stretch it to the closest one.
		if (0 > ray_direction_x)
		{
			cell_step_x = -1;

			x_ray_length = x_ray_unit_length * (ray_start_x - current_cell_x);
		}
		else if (0 < ray_direction_x)
		{
			cell_step_x = 1;

			x_ray_length = x_ray_unit_length * (1 + current_cell_x - ray_start_x);
		}

		if (0 > ray_direction_y)
		{
			cell_step_y = -1;

			y_ray_length = y_ray_unit_length * (ray_start_y - current_cell_y);
		}
		else if (0 < ray_direction_y)
		{
			cell_step_y = 1;

			y_ray_length = y_ray_unit_length * (1 + current_cell_y - ray_start_y);
		}

		while (1)
		{
			//In case the ray hits a corner.
			//I'm a perfectionist (i. e. stupid).
			bool corner_collision = 0;

			//We stretch the shortest ray.
			if (x_ray_length < y_ray_length)
			{
				stripes[a].set_distance(x_ray_length);

				x_ray_length += x_ray_unit_length;

				current_cell_x += cell_step_x;

				if (1 == cell_step_x)
				{
					side = 2;
				}
				else
				{
					side = 0;
				}
			}
			else if (x_ray_length > y_ray_length)
			{
				stripes[a].set_distance(y_ray_length);

				y_ray_length += y_ray_unit_length;

				current_cell_y += cell_step_y;

				if (-1 == cell_step_y)
				{
					side = 3;
				}
				else
				{
					side = 1;
				}
			}
			else //If the rays are equal, that means we hit the corner, so we stretch both rays.
			{
				corner_collision = 1;

				stripes[a].set_distance(x_ray_length);

				x_ray_length += x_ray_unit_length;
				y_ray_length += y_ray_unit_length;

				current_cell_x += cell_step_x;
				current_cell_y += cell_step_y;

				if (1 == cell_step_x)
				{
					side = 2;
				}
				else
				{
					side = 0;
				}
			}

			//Making sure the current cell we're checking is inside our map.
			if (0 <= current_cell_x && 0 <= current_cell_y && gbl::MAP::COLUMNS > current_cell_x && gbl::MAP::ROWS > current_cell_y)
			{
				if (gbl::MAP::Cell::Empty != map[current_cell_x][current_cell_y])
				{
					collision_cell = map[current_cell_x][current_cell_y];

					break;
				}
				else if (1 == corner_collision)
				{
					//The ray can't go through 2 walls standing diagonally.
					if (gbl::MAP::Cell::Empty != map[current_cell_x - cell_step_x][current_cell_y] && gbl::MAP::Cell::Empty != map[current_cell_x][current_cell_y - cell_step_y])
					{
						collision_cell = map[current_cell_x - cell_step_x][current_cell_y];

						break;
					}
				}
			}
			else
			{
				break;
			}
		}

		//Once we hit the wall, we need to find where exactly we hit it to draw the texture correctly.
		if (0 == side % 2)
		{
			side_x = ray_start_y + ray_direction_y * stripes[a].get_distance();
		}
		else
		{
			side_x = ray_start_x + ray_direction_x * stripes[a].get_distance();
		}

		if (2 > side)
		{
			side_x = ceil(side_x) - side_x;
		}
		else
		{
			side_x -= floor(side_x);
		}

		stripes[a].set_angle(normalize_radians(atan2(-ray_direction_y, ray_direction_x)));
		stripes[a].set_side(side);
		stripes[a].set_side_x(side_x);
		stripes[a].set_x(a);

		ray_angle = stripes[a].get_angle() - degrees_to_radians(player.get_direction().x);

		//We're calculating the perpendicular distance when casting rays. But we also need the Eukacfiragridalidian distance to visualize the FOV on the map.
		stripes[a].set_true_distance(stripes[a].get_distance() / abs(cos(ray_angle)));

		switch (collision_cell)
		{
		case gbl::MAP::Cell::Wall:
		{
			stripes[a].set_sprite_name("WALL");
			break;
		}
		case gbl::MAP::Cell::TreeWall:
		{
			stripes[a].set_sprite_name("TREE_WALL");
			break;
		}
		case gbl::MAP::Cell::FinishWall:
		{
			stripes[a].set_sprite_name("FINISH_WALL");
			break;
		}
		case gbl::MAP::Cell::BushWall:
		{
			stripes[a].set_sprite_name("BUSH_WALL");
			break;
		}
		case gbl::MAP::Cell::CaveWall:
		{
			stripes[a].set_sprite_name("CAVE_WALL");
			break;
		}
		case gbl::MAP::Cell::Empty:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void Game::update(float deltaTime)
{
	if (game_state == GameState::GAME_START || game_state == GameState::GAME_VICTORY || game_state == GameState::GAME_END) {
		window.setMouseCursorVisible(true);
	}
	if (game_state == GameState::GAME_PLAYING)
	{
		float player_movement_distance;

		sf::Vector2f player_position = player.get_position();

		player.update(window, map, deltaTime, game_state);

		lulu.update(window, player.get_direction(), player.get_position(), map, deltaTime);

		teemo.update(window, player.get_direction(), player.get_position(), map, deltaTime);

		player_movement_distance = sqrt(pow(player_position.x - player.get_position().x, 2) + pow(player_position.y - player.get_position().y, 2));

		raycast();

		for (Decoration& decoration : decorations)
		{
			decoration.update(player.get_direction(), player.get_position());
		}
	}
}