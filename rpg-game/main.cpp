#include <SFML/Graphics.hpp>    

#include "Player.h"
#include "Enemy.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG Game", sf::Style::Default, settings);
    //window.setFramerateLimit(60);

    Player player;
    Enemy enemy;

    //----------------------------------- INITIALISE -------------------------------------------
    player.Initialize();
    enemy.Initialize();
    //----------------------------------- INITIALISE -------------------------------------------

    //----------------------------------- LOAD -------------------------------------------
    player.Load();
    enemy.Load();
    //----------------------------------- LOAD -------------------------------------------




    while (window.isOpen()) {
        //-----------------------------------UPDATE-------------------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }


        enemy.Update();
        player.Update(enemy);


        //-----------------------------------UPDATE-------------------------------------------



        //-----------------------------------DRAW-------------------------------------------

        //render
        window.clear(sf::Color::Black);
        enemy.Draw(window);
        player.Draw(window);

        window.display();

        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}