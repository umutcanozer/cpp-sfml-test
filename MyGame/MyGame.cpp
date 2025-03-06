#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

sf::Texture idleTexture;
sf::Texture walkTexture;

sf::Clock tickClock;

int main()
{
    int w = 800; int h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    
    idleTexture.loadFromFile("soldier_sprites/_Idle.png");
    walkTexture.loadFromFile("soldier_sprites/_Run.png");
    Player player(&idleTexture, &walkTexture, 125.f);


    sf::Font font;
    sf::Text text;

    if (!font.loadFromFile("arimo.ttf")) {
        std::cerr << "Font yüklenemedi!" << std::endl;
        return -1;
    }

    text.setFont(font); 
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 100);

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
        text.setString("Current state: " + player.GetPlayerState());
        window.clear();
        player.Draw(window);
        window.draw(text);
        window.display();
    }
}
