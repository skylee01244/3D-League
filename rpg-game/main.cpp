#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RPG Game");
    window.setFramerateLimit(60);

    sf::RectangleShape rect;
    sf::Vector2f rectanglePosition(600, 350);
    sf::Vector2f rectangleSize(120, 120);

    rect.setPosition(rectanglePosition);
    rect.setSize(rectangleSize);

    float xVelocity = 3;
    float yVelocity = 3;


    while (window.isOpen()) {

        //-----------------------------------UPDATE-------------------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
        }
        //out of bounds
        if (rectanglePosition.x < 0 || rectanglePosition.x > 1280-120) { xVelocity *= -1; }
        if (rectanglePosition.y < 0 || rectanglePosition.y > 720-120) { yVelocity *= -1; }

        //physics
        rectanglePosition.x += xVelocity;
        rectanglePosition.y += yVelocity;
        rect.setPosition(rectanglePosition);

        //-----------------------------------UPDATE-------------------------------------------



        //-----------------------------------DRAW-------------------------------------------

        //render
        window.clear();
        window.draw(rect);

        window.display();

        //-----------------------------------DRAW-------------------------------------------
    }

    return 0;
}