#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : health(100)
{
}

Enemy::~Enemy()
{
}

void Enemy::ChangeHealth(int hp)
{
    health += hp;
    healthText.setString(std::to_string(health));
}

void Enemy::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Blue);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64);
}

void Enemy::Load()
{
    if (font.loadFromFile("Assets/Fonts/arial.ttf"))
    {
        std::cout << "Arial.ttf font in Assets has been loaded SUCCESSFULLY" << std::endl;
        healthText.setFont(font);
        healthText.setString(std::to_string(health));
    }
    else
    {
        std::cout << "Failed to load Arial.ttf font in Assets" << std::endl;
    }

    if (texture.loadFromFile("Assets/Enemy/Textures/spritesheet.png"))
    {
        std::cout << "Enemy texture loaded!" << std::endl;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(200, 200));

        int XIndex = 0;
        int YIndex = 0;

        sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sprite.scale(sf::Vector2f(2.5, 2.5));


        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
}

void Enemy::Update(float deltaTime)
{
    if (health > 0)
    {
        boundingRectangle.setPosition(sprite.getPosition());
        healthText.setPosition(sprite.getPosition() + sf::Vector2f(0,0));
    }
}

void Enemy::Draw(sf::RenderWindow& window)
{
    if (health > 0)
    {
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(healthText);
    }
}
