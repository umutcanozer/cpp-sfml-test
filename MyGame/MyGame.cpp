#include "SFML/Graphics.hpp"
#include <iostream>
#include <unordered_map>

struct KeyMapping {
    sf::Keyboard::Scancode key;
    sf::Vector2f direction;
};

std::vector<KeyMapping> keyMappings = {
        {sf::Keyboard::Scan::A, {-1.f, 0.f}},
        {sf::Keyboard::Scan::D, {1.f, 0.f}},
        {sf::Keyboard::Scan::W, {0.f, -1.f}},
        {sf::Keyboard::Scan::S, {0.f, 1.f}}
};

void GetRectangleOnCircle(sf::RectangleShape &rectangle, sf::CircleShape &circle) {
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius() * 2, circle.getRadius());
    rectangle.setPosition(circleCenter - sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y / 2));
}

int main()
{
    constexpr float SPEED = 200.0f;
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
        
#pragma region movement
        sf::Vector2f movement(0.f, 0.f);
        for (const auto& key : keyMappings) {
            if (sf::Keyboard::isKeyPressed(key.key)) {
                movement += key.direction;
            }
        }

        float magnitude = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        if (magnitude != 0.f) {
            movement /= magnitude;
            movement *= SPEED * dt;
            circleShape.move(movement);
            GetRectangleOnCircle(rectShape, circleShape);
        }
#pragma endregion


        window.clear();
        window.draw(circleShape);
        window.draw(rectShape);
        window.display();
    }
}
