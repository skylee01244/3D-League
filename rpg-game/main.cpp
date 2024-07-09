#include <SFML/Graphics.hpp>    
#include <iostream>

#include "Headers/FrameRate.h"
#include "Headers/Angles.h"
#include "Headers/Enemy.h"
#include "Headers/Global.h"
#include "Headers/Player.h"

int main()
{
    bool draw_map = 1;
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

    std::chrono::microseconds lag(0);   // make the game framerate-independent

    sf::Event event;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "2D game", sf::Style::Default);
    window.setMouseCursorVisible(100);  // 0 to hide Cursor
    window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
    
    sf::Sprite map_grid_cell_sprite;
    sf::Sprite map_wall_sprite;

    sf::Texture map_grid_cell_texture;
    map_grid_cell_texture.loadFromFile("Resources/Images/MapGridCell.png");

    sf::Texture map_wall_texture;
    map_wall_texture.loadFromFile("Resources/Images/MapWall" + std::to_string(MAP_CELL_SIZE) + ".png");

    Player player(0, 0);

    Steven steven(0, 0);

    map = convert_sketch(player, steven);

    Player player;
    Player2D player2D;
    Enemy enemy;

    //----------------------------------- INITIALISE -------------------------------------------
    frameRate.Initialize();
    player.Initialize();
    player2D.Initialize();
    enemy.Initialize();
    //----------------------------------- INITIALISE -------------------------------------------

    //----------------------------------- LOAD -------------------------------------------
    frameRate.Load();
    player.Load();
    player2D.Load();
    enemy.Load();
    //----------------------------------- LOAD -------------------------------------------

    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0; // You can also just do 1 / seconds
        double fps = 1.0f / deltaTimeTimer.asSeconds(); 

        //-----------------------------------UPDATE-------------------------------------------
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }

        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        frameRate.Update(deltaTime, fps);
        enemy.Update(deltaTime);
        player.Update(deltaTime, enemy, mousePosition);
        player2D.Update(deltaTime, enemy, mousePosition);
        //-----------------------------------UPDATE-------------------------------------------
        
        //-----------------------------------DRAW-------------------------------------------
        window.clear(sf::Color::Black);
        enemy.Draw(window);
        player.Draw(window);
        player2D.Draw(window);
        frameRate.Draw(window);
        window.display();
        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}