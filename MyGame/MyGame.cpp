#include "SFML/Graphics.hpp"
#include <iostream>
#include "Platform.h"
#include "Player.h"

static const float VIEW_HEIGHT = 512.f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
} 

void MouseWheelEvent(const sf::Event& e) {
    if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        std::cout << "wheel type: vertical" << std::endl;
    else if (e.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
        std::cout << "wheel type: horizontal" << std::endl;


    std::cout << "wheel movement: " << e.mouseWheelScroll.delta << std::endl;
    std::cout << "mouse x: " << e.mouseWheelScroll.x << std::endl;
    std::cout << "mouse y: " << e.mouseWheelScroll.y << std::endl;
}

sf::Text DisplayText(sf::Text& text, sf::Font& font) {
    if (!font.loadFromFile("arimo.ttf")) {
        std::cerr << "Font yüklenemedi!" << std::endl;
        return text;
    }

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition({ 0.f, 0.f });

    return text;
}

int main()
{
    int w = 1200; int h = 800;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");
    sf::View gameView(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    sf::Clock tickClock;

    sf::Text stateText;
    sf::Font fontText;
    
    Player playerTest(150.f, 200.f);

    sf::Texture platformTexture;
    platformTexture.loadFromFile("platform_sprites/box.png");
    std::vector<Platform> platforms = {
        {platformTexture, sf::Vector2f(0, 170.f)},
        {platformTexture, sf::Vector2f(0, 25.f)}
    };
    
	sf::Vector2f direction;

    while (window.isOpen())
    {
        sf::Event e;
        
        sf::Time time = tickClock.restart();
        float deltaTime = time.asSeconds();
		if (deltaTime > 1.f / 20.f)
			deltaTime = 1.f / 20.f;
  
        while (window.pollEvent(e))
        {

            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseWheelScrolled:
                MouseWheelEvent(e);
                break;
            case sf::Event::Resized:
                ResizeView(window, gameView);
                break;
            }      
        }

		playerTest.Update(deltaTime);
        gameView.setCenter(playerTest.GetPosition());
        stateText.setString(std::to_string(playerTest.GetVelocityY()));

		for (auto& platform : platforms) {
			if (platform.GetCollider().CheckCollision(playerTest.GetCollider(), direction, 1.f))
                playerTest.OnCollision(direction);
		}

        window.clear();
        window.setView(gameView);
        for (auto& platform : platforms) {
				platform.Draw(window);
        }
		playerTest.Draw(window);
        window.draw(DisplayText(stateText, fontText));
        window.display();
    }
}
