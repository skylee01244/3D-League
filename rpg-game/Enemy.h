#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
private:
	sf::Texture texture;

	sf::Text healthText;
	sf::Font font;


public:
	sf::Sprite sprite;

	sf::RectangleShape boundingRectangle;
	sf::Vector2i size;

	int health;

public:
	Enemy();
	~Enemy();

	void ChangeHealth(int hp);
	
	void Initialize();	// Called once per Program
	void Load();		// Called once per Program

	void Update(float deltaTime);		// Called once per frame
	void Draw(sf::RenderWindow& window);		// Called once per frame
};
