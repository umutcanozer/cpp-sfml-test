#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Vector2f pos);
	~Platform();

	void Draw(sf::RenderWindow& window);
	
	sf::Sprite GetBody() { return platformSprite; };
	Collider& GetCollider() { return platformCollider; };

private:
	sf::Sprite platformSprite;
	static sf::Texture platformTexture;
	sf::IntRect platformRect;

	Collider platformCollider;
};

