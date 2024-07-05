#include <iostream>
#include "Player.h"
#include "Math.h"

void Player::Initialize()
{
}

void Player::Load()
{
    if (texture.loadFromFile("Assets/Player/Textures/spritesheet.png"))
    {
        std::cout << "Player texture loaded!" << std::endl;
        sprite.setTexture(texture);

        int XIndex = 0;
        int YIndex = 0;

        sprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(2.5, 2.5));
    }
    else
    {
        std::cout << "Player texture failed to load!" << std::endl;
    }
    sf::Vector2f playerPosition(sf::Vector2f(1920 / 2 - 64, 1080 / 2 - 64));
    sprite.setPosition(playerPosition);
}

void Player::Update(Enemy& enemy)
{
    // Movement
    int playerVelocity = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(0, -playerVelocity));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(-playerVelocity, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(0, playerVelocity));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(playerVelocity, 0));
    }

    //out of bounds
    sf::Vector2f position = sprite.getPosition();
    if (position.x < 0) {
        sprite.setPosition(0, position.y);
    }
    if (position.x > 1920 - 64 * 2.5) {
        sprite.setPosition(1920 - 64 * 2.5, position.y);
    }
    if (position.y < 0) {
        sprite.setPosition(position.x, 0);
    }
    if (position.y > 1080 - 64 * 2.5) {
        sprite.setPosition(position.x, 1080 - 64 * 2.5);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        bullets.push_back(sf::RectangleShape(sf::Vector2f(50, 25)));
        int i = bullets.size() - 1;
        bullets[i].setPosition(sprite.getPosition());
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        sf::Vector2f bulletdirection = enemy.sprite.getPosition() - bullets[i].getPosition();
        bulletdirection = Math::NormaliseVector(bulletdirection);
        bullets[i].setPosition(bullets[i].getPosition() + bulletdirection * bulletSpeed);
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    for (size_t i = 0; i < bullets.size(); i++) {
        window.draw(bullets[i]);
    }
}
