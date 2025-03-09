#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"
#include "Platform.h"

sf::Texture idleTexture;
sf::Texture walkTexture;
sf::Clock tickClock;

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
    sf::Text stateText;
    sf::Font fontText;

    Player player(125.f, 150.f);
    Platform platform1(sf::Vector2f(500.f, 200.f), sf::Vector2f(0.f, 100.f));
	sf::Vector2f direction;

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time time = tickClock.restart();
        float dt = time.asSeconds();

		if (dt > 1.f / 20.f)
			dt = 1.f / 20.f;
  
        while (window.pollEvent(event))
        {

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseWheelScrolled:
                MouseWheelEvent(event);
                break;
            case sf::Event::Resized:
                ResizeView(window, gameView);
                break;
            }      
        }

      
        player.Update(dt);
        gameView.setCenter(player.GetPosition());
        stateText.setString("X velocity: "+std::to_string(player.GetPlayerVelocityX()) + "Y velocity: " + std::to_string(player.GetPlayerVelocityY()));

		if (platform1.GetCollider().CheckCollision(player.GetCollider(), direction, 1.f))
			player.OnCollision(direction);

        window.clear();
        window.setView(gameView);
        platform1.Draw(window);
        player.Draw(window);
        window.draw(DisplayText(stateText, fontText));
        window.display();
    }
}
