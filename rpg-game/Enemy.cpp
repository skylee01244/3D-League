#include "Enemy.h"
#include <iostream>

void Enemy::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Blue);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64);
}

void Enemy::Load()
{
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
    boundingRectangle.setPosition(sprite.getPosition());
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
}
