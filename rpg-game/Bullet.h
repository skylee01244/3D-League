#pragma once
#include <SFML/Graphics.hpp>    
class Bullet
{
private:
	float speed;
	sf::RectangleShape rectangleShape;
	sf::Vector2f direction;

public:
	Bullet();
	~Bullet();
	void SetDirection();
	void Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	inline const sf::FloatRect& GetGloabBounds() { return rectangleShape.getGlobalBounds(); }
};

