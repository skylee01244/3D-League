#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

sf::Vector2f NormaliseVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    sf::Vector2f normalisedVector;
    normalisedVector.x = vector.x / m;
    normalisedVector.y = vector.y / m;
    return normalisedVector;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG Game", sf::Style::Default, settings);
    //window.setFramerateLimit(60);

    std::vector<sf::RectangleShape> bullets;


    float bulletSpeed = 0.5f;

    //-----------------------------------LOAD-------------------------------------------
    //-----------------------------------ENEMY-------------------------------------------
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;

    if (enemyTexture.loadFromFile("Assets/Enemy/Textures/spritesheet.png"))
    {
        std::cout << "Enemy texture loaded!" << std::endl;
        enemySprite.setTexture(enemyTexture);
        enemySprite.setPosition(sf::Vector2f(200, 200));

        int XIndex = 0;
        int YIndex = 0;

        enemySprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        enemySprite.scale(sf::Vector2f(2.5, 2.5));
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
    //-----------------------------------ENEMY-------------------------------------------
    //-----------------------------------PLAYER-------------------------------------------
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    if (playerTexture.loadFromFile("Assets/Player/Textures/spritesheet.png"))
    {
        std::cout << "Player texture loaded!" << std::endl;
        playerSprite.setTexture(playerTexture);

        int XIndex = 0;
        int YIndex = 0;

        playerSprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        playerSprite.scale(sf::Vector2f(2.5, 2.5));
    }
    else
    {
        std::cout << "Player texture failed to load!" << std::endl;
    }
    sf::Vector2f playerPosition(sf::Vector2f(1920 / 2 - 64, 1080 / 2 - 64));
    playerSprite.setPosition(playerPosition);
    //-----------------------------------PLAYER-------------------------------------------
    //-----------------------------------LOAD-------------------------------------------



    while (window.isOpen()) {
        //-----------------------------------UPDATE-------------------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }


        // Movement
        int playerVelocity = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, -playerVelocity));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(-playerVelocity, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, playerVelocity));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(playerVelocity, 0));
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            bullets.push_back(sf::RectangleShape(sf::Vector2f(50, 25)));
            int i = bullets.size() - 1;
            bullets[i].setPosition(playerSprite.getPosition());            
        }

        for (size_t i = 0; i < bullets.size(); i++) 
        {
            sf::Vector2f bulletdirection = enemySprite.getPosition() - bullets[i].getPosition();
            bulletdirection = NormaliseVector(bulletdirection);
            bullets[i].setPosition(bullets[i].getPosition() + bulletdirection * bulletSpeed);
        }


        //out of bounds

        sf::Vector2f position = playerSprite.getPosition();
        if (position.x < 0) {
            playerSprite.setPosition(0, position.y);
        }
        if (position.x > 1920 - 64 * 2.5) {
            playerSprite.setPosition(1920 - 64 * 2.5, position.y);
        }
        if (position.y < 0) {
            playerSprite.setPosition(position.x, 0);
        }
        if (position.y > 1080 - 64 * 2.5) {
            playerSprite.setPosition(position.x, 1080 - 64 * 2.5);
        }

        //-----------------------------------UPDATE-------------------------------------------



        //-----------------------------------DRAW-------------------------------------------

        //render
        window.clear();
        window.draw(enemySprite);
        window.draw(playerSprite);
        for (size_t i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i]);
        }
        window.display();

        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}