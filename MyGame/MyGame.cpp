﻿#include "SFML/Graphics.hpp"
#include <iostream>
#include "Platform.h"
#include "Player.h"
#include "Projectile.h"

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
    if (!font.loadFromFile("assets/arimo.ttf")) {
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

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets/background_sprites/Background.png");
	sf::Sprite background(backgroundTexture);
	
    sf::Vector2f viewSize = gameView.getSize();
    float scaleX = viewSize.x / backgroundTexture.getSize().x;
    float scaleY = viewSize.y / backgroundTexture.getSize().y;
    background.setScale(scaleX, scaleY);
    background.setPosition(gameView.getCenter().x - viewSize.x / 2,
        gameView.getCenter().y - viewSize.y / 2);

    sf::Clock tickClock;
    sf::Text stateText;
    sf::Font fontText;
    
    Player player(150.f, 150.f);
    
    std::vector<Platform> platforms = {
        {sf::Vector2f(0, 25.f)},
        {sf::Vector2f(150, 25.f)},
        {sf::Vector2f(150, 170.f)},
        {sf::Vector2f(-150, 170.f)},
        {sf::Vector2f(150, -120.f)},
        {sf::Vector2f(-150, -120.f)},
        {sf::Vector2f(-150, 25.f)},
    };

    std::vector<Projectile> projectiles = {
        {50.f, sf::Vector2f(-100.f, 8.f)}
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

		player.Update(deltaTime);

        for (auto& projectile : projectiles) {
            projectile.Update(deltaTime);
        }

        stateText.setString(std::to_string(player.GetVelocityY()));
 
		for (auto& platform : platforms) {
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.f))
                player.OnCollision(direction);
		}

        for (auto& projectile : projectiles) {
            if (projectile.GetCollider().CheckCollision(player.GetCollider(), direction, 1.f))
                projectiles.pop_back();
        }

        window.clear();
        window.setView(gameView);
		window.draw(background);
        for (auto& platform : platforms) {
				platform.Draw(window);
        }

        for (auto& projectile : projectiles) {
            projectile.Draw(window);
        }

		player.Draw(window);
        window.draw(DisplayText(stateText, fontText));
        window.display();
    }
}
