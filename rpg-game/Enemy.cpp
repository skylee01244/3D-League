#include "Enemy.h"
#include <iostream>

void Enemy::Initialize()
{
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

        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(2.5, 2.5));
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
}

void Enemy::Update()
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
