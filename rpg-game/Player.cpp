#include <array>
#include <chrono>
#include <iostream>
#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h> // For macOS
#elif defined(_WIN32)
#include <windows.h> // For Windows
#endif
#include <SFML/Graphics.hpp>

#include "Headers/AngleFunctions.h"
#include "Headers/Global.h"
#include "Headers/MapCollision.h"
#include "Headers/Player.h"

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

//void Player::update(const sf::RenderWindow& i_window, const gbl::MAP::Map<>& i_map)
//{
//	if (1 == i_window.hasFocus())
//	{
//		float rotation_horizontal = 0;
//		float rotation_vertical = 0;
//		float step_x = 0;
//		float step_y = 0;
//
//		unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * i_window.getSize().x));
//		unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * i_window.getSize().y));
//
//		rotation_horizontal = gbl::RAYCASTING::FOV_HORIZONTAL * (window_center_x - sf::Mouse::getPosition(i_window).x) / i_window.getSize().x;
//		rotation_vertical = gbl::RAYCASTING::FOV_VERTICAL * (window_center_y - sf::Mouse::getPosition(i_window).y) / i_window.getSize().y;
//
//		direction.x = get_degrees(direction.x + rotation_horizontal);
//		direction.y = std::clamp<float>(direction.y + rotation_vertical, -gbl::RAYCASTING::MAX_VERTICAL_DIRECTION, gbl::RAYCASTING::MAX_VERTICAL_DIRECTION);
//
//		sf::Mouse::setPosition(sf::Vector2i(window_center_x, window_center_y), i_window);
//
//		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//		{
//			step_x = gbl::PLAYER::MOVEMENT_SPEED * cos(deg_to_rad(90 + direction.x));
//			step_y = -gbl::PLAYER::MOVEMENT_SPEED * sin(deg_to_rad(90 + direction.x));
//		}
//		else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//		{
//			step_x = gbl::PLAYER::MOVEMENT_SPEED * cos(deg_to_rad(direction.x - 90));
//			step_y = -gbl::PLAYER::MOVEMENT_SPEED * sin(deg_to_rad(direction.x - 90));
//		}
//
//		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//		{
//			step_x -= gbl::PLAYER::MOVEMENT_SPEED * cos(deg_to_rad(direction.x));
//			step_y += gbl::PLAYER::MOVEMENT_SPEED * sin(deg_to_rad(direction.x));
//		}
//		else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//		{
//			step_x += gbl::PLAYER::MOVEMENT_SPEED * cos(deg_to_rad(direction.x));
//			step_y -= gbl::PLAYER::MOVEMENT_SPEED * sin(deg_to_rad(direction.x));
//		}
//
//		if (0 == map_collision(step_x + position.x, step_y + position.y, i_map))
//		{
//			position.x += step_x;
//			position.y += step_y;
//		}
//		else if (0 == map_collision(step_x + position.x, position.y, i_map))
//		{
//			position.x += step_x;
//			position.y = round(position.y);
//		}
//		else if (0 == map_collision(position.x, step_y + position.y, i_map))
//		{
//			position.x = round(position.x);
//			position.y += step_y;
//		}
//		else
//		{
//			position.x = round(position.x);
//			position.y = round(position.y);
//		}
//	}
//}

//void Player::update(const sf::RenderWindow& i_window, const gbl::MAP::Map<>& i_map)
//{
//    if (1 == i_window.hasFocus())
//    {
//        float rotation_horizontal = 0;
//        float rotation_vertical = 0;
//
//        unsigned short window_center_x = static_cast<unsigned short>(round(0.5f * i_window.getSize().x));
//        unsigned short window_center_y = static_cast<unsigned short>(round(0.5f * i_window.getSize().y));
//
//        rotation_horizontal = gbl::RAYCASTING::FOV_HORIZONTAL * (window_center_x - sf::Mouse::getPosition(i_window).x) / i_window.getSize().x;
//        rotation_vertical = gbl::RAYCASTING::FOV_VERTICAL * (window_center_y - sf::Mouse::getPosition(i_window).y) / i_window.getSize().y;
//
//        direction.x = get_degrees(direction.x + rotation_horizontal);
//        direction.y = std::clamp<float>(direction.y + rotation_vertical, -gbl::RAYCASTING::MAX_VERTICAL_DIRECTION, gbl::RAYCASTING::MAX_VERTICAL_DIRECTION);
//
//        sf::Mouse::setPosition(sf::Vector2i(window_center_x, window_center_y), i_window);
//    }
//}

void Player::update(const sf::RenderWindow& i_window, const gbl::MAP::Map<>& i_map, float deltaTime)
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
        // Get the mouse delta for Windows
        POINT mousePos;
        static POINT lastMousePos = { 0, 0 };
        GetCursorPos(&mousePos);

        deltaX = static_cast<float>(mousePos.x - lastMousePos.x);
        deltaY = static_cast<float>(mousePos.y - lastMousePos.y);

        lastMousePos = mousePos;
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