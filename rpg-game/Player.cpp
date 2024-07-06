#include <iostream>
#include "Player.h"
#include "Math.h"

Player::Player() : bulletSpeed(0.3f), playerSpeed(1.0f), maxFireRate(250), fireRateTimer(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64);
}

void Player::Load()
{
    if (texture.loadFromFile("Assets/Player/Textures/spritesheet.png"))
    {
        std::cout << "Player texture loaded!" << std::endl;
        sprite.setTexture(texture);

        int XIndex = 0;
        int YIndex = 0;

        sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sprite.scale(sf::Vector2f(2.5, 2.5));


        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    }
    else
    {
        std::cout << "Player texture failed to load!" << std::endl;
    }
    sf::Vector2f playerPosition(sf::Vector2f(1920 / 2 - 64, 1080 / 2 - 64));
    sprite.setPosition(playerPosition);
}

void Player::Update(float deltaTime, Enemy& enemy)
{
    // Movement
    int playerVelocity = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(0, -playerVelocity) * playerSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(-playerVelocity, 0) * playerSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(0, playerVelocity) * playerSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(playerVelocity, 0) * playerSpeed * deltaTime);
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

    //----------------------------------------------------------------------------------------------------------
    fireRateTimer += deltaTime;
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= maxFireRate)
    {
        bullets.push_back(sf::RectangleShape(sf::Vector2f(50, 25)));
        int i = bullets.size() - 1;
        bullets[i].setPosition(sprite.getPosition());

        fireRateTimer = 0;
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        sf::Vector2f bulletdirection = enemy.sprite.getPosition() - bullets[i].getPosition();
        bulletdirection = Math::NormaliseVector(bulletdirection);
        bullets[i].setPosition(bullets[i].getPosition() + bulletdirection * bulletSpeed * deltaTime);

        if (Math::DidRectCollide(bullets[i].getGlobalBounds(), enemy.sprite.getGlobalBounds()))
        {
            enemy.ChangeHealth(-10);
            bullets.erase(bullets.begin() + i);
            std::cout << "COLLISION" << std::endl;
        }
    }

    boundingRectangle.setPosition(sprite.getPosition());
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
    for (size_t i = 0; i < bullets.size(); i++) {
        window.draw(bullets[i]);
    }
}
