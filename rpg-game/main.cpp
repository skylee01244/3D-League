#include <SFML/Graphics.hpp>    
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "FrameRate.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG Game", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0); // Set to 0 to remove any cap


    FrameRate frameRate;
    Player player;
    Enemy enemy;

    //----------------------------------- INITIALISE -------------------------------------------
    frameRate.Initialize();
    player.Initialize();
    enemy.Initialize();
    //----------------------------------- INITIALISE -------------------------------------------

    //----------------------------------- LOAD -------------------------------------------
    frameRate.Load();
    player.Load();
    enemy.Load();
    //----------------------------------- LOAD -------------------------------------------

    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0; // You can also just do 1 / seconds
        double fps = 1.0f / deltaTimeTimer.asSeconds();

        //-----------------------------------UPDATE-------------------------------------------
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }

        frameRate.Update(deltaTime, fps);
        enemy.Update(deltaTime);
        player.Update(deltaTime, enemy);
        //-----------------------------------UPDATE-------------------------------------------
        
        //-----------------------------------DRAW-------------------------------------------
        window.clear(sf::Color::Black);
        enemy.Draw(window);
        player.Draw(window);
        frameRate.Draw(window);
        window.display();
        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}