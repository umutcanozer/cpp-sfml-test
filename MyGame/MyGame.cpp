#include "SFML/Graphics.hpp"
#include <iostream>



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

/*void getRectangleOnCircle(sf::RectangleShape& rectangle, sf::CircleShape& circle) {
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), .0f);
    rectangle.setPosition(circleCenter - sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y / 2));
}*/

int main()
{
    constexpr float SPEED = 200.0f;
    constexpr float ROTATE_SPEED = .1f;

    int w = 600; int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    sf::Clock clock;

    sf::RectangleShape rectShape({30.f, 75.f});
    rectShape.setOrigin(rectShape.getSize().x / 2, rectShape.getSize().y / 2);
    rectShape.setPosition({100.f, 100.f});

    sf::Texture playerTexture;
    playerTexture.loadFromFile("sprites/test_texture.jpg");
    rectShape.setTexture(&playerTexture);
    

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
            rectShape.move(movement);
        }
#pragma endregion

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {
            //rotate
        }


        window.clear();
        window.draw(rectShape);
        window.display();
    }
}
