#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 720), "RPG Game"); //(1280, 720)
    window.setFramerateLimit(60);

    //Rectangle 1 (Left)
    sf::RectangleShape rect1;
    sf::Vector2f rect1Position(430, 350);
    sf::Vector2f rect1Size(100, 100);

    rect1.setPosition(rect1Position);
    rect1.setSize(rect1Size);

    sf::Vector2f rect1Velocity(-1, 0);

    //Rectangle 2 (Right)
    sf::RectangleShape rect2;
    sf::Vector2f rect2Position(855, 350);
    sf::Vector2f rect2Size(100, 100);

    rect2.setPosition(rect2Position);
    rect2.setSize(rect2Size);
    
    sf::Vector2f rect2Velocity(1, 0);


    while (window.isOpen()) {

        //-----------------------------------UPDATE-------------------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }
        //out of bounds
        if (rect1Position.x < 0 || rect1Position.x > 1000 -100) { rect1Velocity.x *= -1; }
        if (rect1Position.y < 0 || rect1Position.y > 720-100) { rect1Velocity.y *= -1; }

        if (rect2Position.x < 0 || rect2Position.x > 1000 - 100) { rect2Velocity.x *= -1; }
        if (rect2Position.y < 0 || rect2Position.y > 720 - 100) { rect2Velocity.y *= -1; }

        // Head on collision
        if (rect1Position.x + 100 > rect2Position.x && rect1Position.y + 100 > rect2Position.y && rect1Position.y < rect2Position.y) {
            rect1Velocity.x *= -1;
            rect2Velocity.x *= -1;
            std::cout << "HEAD ON COLLISION" << std::endl;
        }
        // Reverse Head on collision
        else if (rect1Position.x < rect2Position.x + 100 && rect1Position.y + 100 > rect2Position.y && rect1Position.y < rect2Position.y) {
            rect1Velocity.x *= -1;
            rect2Velocity.x *= -1;
            std::cout << "REVERSE HEAD ON COLLISION" << std::endl;
        }
        // On top collision
        else if (rect1Position.y < rect2Position.y + 100 && rect1Position.x + 100 > rect2Position.x && rect1Position.x < rect2Position.x) {
            rect1Velocity.y *= -1;
            rect2Velocity.y *= -1;
            std::cout << "ON TOP COLLISION" << std::endl;
        }
        // On bottom collision
        else if (rect1Position.y + 100 > rect2Position.y && rect1Position.x + 100 > rect2Position.x && rect1Position.x < rect2Position.x) {
            rect1Velocity.y *= -1;
            rect2Velocity.y *= -1;
            std::cout << "BELOW COLLISION" << std::endl;
        }

        //physics
        rect1Position.x += rect1Velocity.x;
        rect1Position.y += rect1Velocity.y;
        rect1.setPosition(rect1Position);

        rect2Position.x += rect2Velocity.x;
        rect2Position.y += rect2Velocity.y;
        rect2.setPosition(rect2Position);

        //-----------------------------------UPDATE-------------------------------------------



        //-----------------------------------DRAW-------------------------------------------

        //render
        window.clear();
        window.draw(rect1);
        window.draw(rect2);

        window.display();

        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}