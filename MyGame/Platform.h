#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Vector2f pos);
	~Platform();

	void Draw(sf::RenderWindow& window);
	sf::Sprite GetBody() { return spritePlatform; };
	Collider& GetCollider() { return platformCollider; };

	void SetTexture(sf::Texture* texture) { spritePlatform.setTexture(*texture); };
private:
	sf::Sprite spritePlatform;
	Collider platformCollider;

	sf::IntRect platformRect;
	sf::Texture platformTexture;
};

