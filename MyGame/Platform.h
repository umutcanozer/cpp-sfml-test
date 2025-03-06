#pragma once
#include "SFML/Graphics.hpp"

class Platform
{
public:
	Platform(sf::Vector2f size, sf::Vector2f pos);
	~Platform();

	void Draw(sf::RenderWindow& window);
	sf::RectangleShape GetBody() { return body; };
private:
	sf::RectangleShape body;
};

