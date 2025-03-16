#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Collider.h"

class Projectile
{
public:
	Projectile(float movementSpeed, sf::Vector2f pos);
	~Projectile();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Sprite GetBody() { return projectileSprite; };
	Collider& GetCollider() { return projectileCol; };
	sf::Vector2f GetPosition() { return projectileSprite.getPosition(); };
private:
	sf::Sprite projectileSprite;
	static sf::Texture projectileTexture;
	
	float movementSpeed;
	bool faceRight;
	sf::Vector2f velocity;

	Animation projectileAnim;
	TextureConfig animConfig;

	Collider projectileCol;
};

