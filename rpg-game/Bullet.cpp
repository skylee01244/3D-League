#include "Bullet.h"
#include "Math.h"

Bullet::Bullet() : speed(0.0f)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetDirection()
{
}

void Bullet::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed)
{
	rectangleShape.setSize(sf::Vector2f(50, 25));
	rectangleShape.setPosition(position);
	direction = Math::NormaliseVector(target - position);
	this->speed = speed;
}

void Bullet::Update(float deltaTime)
{
	rectangleShape.setPosition(rectangleShape.getPosition() + direction * speed * deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(rectangleShape);
}
