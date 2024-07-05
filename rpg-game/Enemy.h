#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
private:
	sf::Texture texture;

public:
	sf::Sprite sprite;

public:
	void Initialize();	// Called once per Program
	void Load();		// Called once per Program

	void Update();		// Called once per frame
	void Draw(sf::RenderWindow& window);		// Called once per frame
};
