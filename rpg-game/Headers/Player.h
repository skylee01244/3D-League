#pragma once

class Player
{
private:
	sf::Vector2f direction;
	sf::Vector2f position;
	bool moving_left = false;
	bool moving_right = false;
	bool moving_forward = false;
	bool moving_backward = false;
public:
	Player(const float i_x = 0, const float i_y = 0);

	void set_position(const float i_x, const float i_y);
	void update(const sf::RenderWindow& i_window, const gbl::MAP::Map<>& i_map);
	void handle_movement_events(const sf::Event& event, const gbl::MAP::Map<>& i_map);

	sf::Vector2f get_direction() const;
	sf::Vector2f get_position() const;
};