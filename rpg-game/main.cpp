#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RPG Game", sf::Style::Default, settings);
    //window.setFramerateLimit(60);


    //-----------------------------------LOAD-------------------------------------------
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    if (playerTexture.loadFromFile("Assets/Player/Textures/spritesheet.png"))
    {
        std::cout << "Player image loaded!" << std::endl;
        playerSprite.setTexture(playerTexture);

        int XIndex = 0;
        int YIndex = 0;

        playerSprite.setTextureRect(sf::IntRect(XIndex * 64, YIndex * 64, 64, 64));
        playerSprite.scale(sf::Vector2f(2.5, 2.5));
    }
    else
    {
        std::cout << "Player image failed to load!" << std::endl;
    }
    
    //-----------------------------------LOAD-------------------------------------------


    sf::Vector2f playerPosition(sf::Vector2f(1280 / 2, 720 / 2));
    playerSprite.setPosition(playerPosition);



    while (window.isOpen()) {

        //-----------------------------------UPDATE-------------------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }
        //out of bounds

        sf::Vector2f position = playerSprite.getPosition();
        if (position.x < 0) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, position.y));
        }
        if (position.x > 1280 - 64 * 3) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(1280 - 64 * 3, position.y));
        }
        if (position.y < 0) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(position.x, 0));
        }
        if (position.y > 720 - 64 * 3) {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(position.x, 720 - 64 * 3));
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


        //-----------------------------------UPDATE-------------------------------------------



        //-----------------------------------DRAW-------------------------------------------

        //render
        window.clear();
        window.draw(playerSprite);
        window.display();

        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}