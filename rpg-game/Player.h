#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Player
{
private:
	sf::Texture texture;

	std::vector<sf::RectangleShape> bullets;
	float bulletSpeed = 0.3f;
	float playerSpeed = 1.0f;
	sf::RectangleShape boundingRectangle;

	sf::Vector2i size;
public:
	sf::Sprite sprite;

public:
	void Initialize();	// Called once per Program
	void Load();		// Called once per Program

	void Update(float deltaTime, Enemy& enemy);		// Called once per frame
	void Draw(sf::RenderWindow& window);		// Called once per frame
};

