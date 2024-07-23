#include <array>
#include <chrono>
#include <iostream>
#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h> // For macOS
#endif
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Global.h"
#include "Headers/MapCollision.h"
#include "Headers/Player.h"
#include "Headers/Game.h"

Player::Player(const float i_x, const float i_y) :
	direction(0, 0),
	position(i_x, i_y)
{
}

void Player::set_position(const float i_x, const float i_y)
{
	position.x = i_x;
	position.y = i_y;
}

void Player::update(const sf::RenderWindow& i_window, const gbl::MAP::Map<>& i_map, float deltaTime, bool& game_victory)
{
    if (i_window.hasFocus())
    {
        float deltaX = 0;
        float deltaY = 0;

#ifdef __APPLE__
        // Get the mouse delta for macOS
        int32_t macDeltaX, macDeltaY;
        CGGetLastMouseDelta(&macDeltaX, &macDeltaY);
        deltaX = static_cast<float>(macDeltaX);
        deltaY = static_cast<float>(macDeltaY);
#elif defined(_WIN32)
        // Get the mouse delta for Windows using SFML functions
        static sf::Vector2i lastMousePosition = sf::Mouse::getPosition(i_window);
        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(i_window);

        // Center of the window
        unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * i_window.getSize().x));
        unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * i_window.getSize().y));
        sf::Vector2i window_center(window_center_x, window_center_y);

        deltaX = static_cast<float>(currentMousePosition.x - window_center.x);
        deltaY = static_cast<float>(currentMousePosition.y - window_center.y);

        // Reset mouse position to the center
        sf::Mouse::setPosition(window_center, i_window);
#endif

        // Calculate rotations based on the delta
        float rotation_horizontal = -gbl::RAYCASTING::FOV_HORIZONTAL * deltaX / i_window.getSize().x;
        float rotation_vertical = -gbl::RAYCASTING::FOV_VERTICAL * deltaY / i_window.getSize().y;

        direction.x = get_degrees(direction.x + rotation_horizontal);
        direction.y = std::clamp<float>(direction.y + rotation_vertical, -gbl::RAYCASTING::MAX_VERTICAL_DIRECTION, gbl::RAYCASTING::MAX_VERTICAL_DIRECTION);

        // Key movement
        float step_x = 0;
        float step_y = 0;

        if (moving_left)
        {
            step_x = gbl::PLAYER::MOVEMENT_SPEED * deltaTime * cos(deg_to_rad(90 + direction.x));
            step_y = -gbl::PLAYER::MOVEMENT_SPEED * deltaTime * sin(deg_to_rad(90 + direction.x));
        }
        if (moving_right)
        {
            step_x = gbl::PLAYER::MOVEMENT_SPEED * deltaTime * cos(deg_to_rad(direction.x - 90));
            step_y = -gbl::PLAYER::MOVEMENT_SPEED * deltaTime * sin(deg_to_rad(direction.x - 90));
        }
        if (moving_backward)
        {
            step_x -= gbl::PLAYER::MOVEMENT_SPEED * deltaTime * cos(deg_to_rad(direction.x));
            step_y += gbl::PLAYER::MOVEMENT_SPEED * deltaTime * sin(deg_to_rad(direction.x));
        }
        if (moving_forward)
        {
            step_x += gbl::PLAYER::MOVEMENT_SPEED * deltaTime * cos(deg_to_rad(direction.x));
            step_y -= gbl::PLAYER::MOVEMENT_SPEED * deltaTime * sin(deg_to_rad(direction.x));
        }

        if (1 == finish_collision(step_x + position.x, step_y + position.y, i_map))
        {
            game_victory = true;
        }

        /*if (finish_collision(step_x + position.x, step_y + position.y, i_map) ||
            finish_collision(step_x + position.x, position.y, i_map) ||
            finish_collision(position.x, step_y + position.y, i_map))
        {
            game_victory = true;
            if(finish_collision(step_x + position.x, step_y + position.y, i_map)) { std::cout << "1" << std::endl; }
            if (finish_collision(step_x + position.x, position.y, i_map)) { std::cout << "2" << std::endl; }
            if (finish_collision(position.x, step_y + position.y, i_map)) { std::cout << "3" << std::endl; }
            
        }*/

        if (0 == map_collision(step_x + position.x, step_y + position.y, i_map))
        {
            position.x += step_x;
            position.y += step_y;
        }
        else if (0 == map_collision(step_x + position.x, position.y, i_map))
        {
            position.x += step_x;
            position.y = round(position.y);
        }
        else if (0 == map_collision(position.x, step_y + position.y, i_map))
        {
            position.x = round(position.x);
            position.y += step_y;
        }
        else
        {
            position.x = round(position.x);
            position.y = round(position.y);
        }
    }
    else
    {
        // If the window is not focused, reset the last mouse position to the center
        unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * i_window.getSize().x));
        unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * i_window.getSize().y));
        sf::Mouse::setPosition(sf::Vector2i(window_center_x, window_center_y), i_window);
    }
}


void Player::handle_movement_events(const sf::Event& event, const gbl::MAP::Map<>& i_map)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::A:
            moving_left = true;
            break;
        case sf::Keyboard::D:
            moving_right = true;
            break;
        case sf::Keyboard::S:
            moving_backward = true;
            break;
        case sf::Keyboard::W:
            moving_forward = true;
            break;
        default:
            break;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::A:
            moving_left = false;
            break;
        case sf::Keyboard::D:
            moving_right = false;
            break;
        case sf::Keyboard::S:
            moving_backward = false;
            break;
        case sf::Keyboard::W:
            moving_forward = false;
            break;
        default:
            break;
        }
    }
}

sf::Vector2f Player::get_direction() const
{
	return direction;
}

sf::Vector2f Player::get_position() const
{
	return position;
}