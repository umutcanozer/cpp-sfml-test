#include "SFML/Graphics.hpp"
#include <iostream>


void GetRectangleOnCircle(sf::RectangleShape &rectangle, sf::CircleShape &circle) {
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius() * 2, circle.getRadius());
    rectangle.setPosition(circleCenter - sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y / 2));
}


int main()
{
    int w = 600; int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    sf::Clock clock;

    sf::RectangleShape rectShape({25.f, 25.f});
    rectShape.setFillColor(sf::Color::Cyan);

    sf::CircleShape circleShape(150.f);
    circleShape.setFillColor(sf::Color::Blue);

    GetRectangleOnCircle(rectShape, circleShape);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
#pragma region mousewheel 
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;


                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            }
#pragma endregion
        }


        /* TODO:
        * vector magnitude = sqrt(x^2 + y^2)
        * adjust movement system and vectors
        */

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            circleShape.move(-1.f * dt * 50.f, 0.f);
            GetRectangleOnCircle(rectShape, circleShape);
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            circleShape.move(+1.f * dt * 50.f, 0.f);
            GetRectangleOnCircle(rectShape, circleShape);
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            circleShape.move(0.f, -1.f * dt * 50.f);
            GetRectangleOnCircle(rectShape, circleShape);
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            circleShape.move(0.f, +1.f * dt * 50.f);
            GetRectangleOnCircle(rectShape, circleShape);
        }
        
        window.clear();
        window.draw(circleShape);
        window.draw(rectShape);
        window.display();
    }
}
