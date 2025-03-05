#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

sf::Texture idleTexture;
sf::Texture walkTexture;

sf::Clock tickClock;

int main()
{
    //currently not working as i wanted
    int w = 800; int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    
    idleTexture.loadFromFile("soldier_sprites/_Idle.png");
    walkTexture.loadFromFile("soldier_sprites/_Run.png");
    //idle anim has 10 sprites
    //running anim has 10 sprites
    Player player(&idleTexture, &walkTexture, 10, .2f, 250.f);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time time = tickClock.restart();
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
