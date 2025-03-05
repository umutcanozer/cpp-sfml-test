#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"


int main()
{
    int w = 600; int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    sf::Clock clock;

    sf::Texture playerTexture;
    playerTexture.loadFromFile("sprites/test_texture.jpg");
    
    Player player(&playerTexture ,150.f);

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
       
        player.Update(dt);

        window.clear();
        player.Draw(window);
        window.display();
    }
}
