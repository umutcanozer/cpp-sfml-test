#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Texture& texture, sf::Vector2f pos);
	~Platform();

	void Draw(sf::RenderWindow& window);
	sf::Sprite GetBody() { return spritePlatform; };
	Collider& GetCollider() { return platformCollider; };

private:
	sf::Sprite spritePlatform;
	Collider platformCollider;

	sf::IntRect platformRect;
};

