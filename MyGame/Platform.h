#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Vector2f size, sf::Vector2f pos);
	~Platform();

	void Draw(sf::RenderWindow& window);
	sf::RectangleShape GetBody() { return body; };
	Collider& GetCollider() { return platformCollider; };
private:
	sf::RectangleShape body;
	Collider platformCollider;
};

