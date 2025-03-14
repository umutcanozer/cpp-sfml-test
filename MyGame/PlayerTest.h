#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"
#include "Animation.h"
#include <unordered_map>

struct KeyMapping {
	sf::Keyboard::Key key;
	float direction;
};

enum class PState {
	Idle,
	Walk
};

class PlayerTest
{
public:
	PlayerTest(float movementSpeed, float jumpForce);
	~PlayerTest();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	Collider& GetCollider() { return playerCollider; };
	sf::Vector2f GetPosition() { return playerSprite.getPosition(); };

	std::string GetPlayerState();
private:
	void SetTexture();

private:
	float movementSpeed;
	float jumpForce;

	bool canJump;
	bool faceRight;

	float xOffset;
	float yOffset;

	sf::Sprite playerSprite;
	sf::Vector2f velocity;

	sf::RectangleShape test;

	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture* currentTexture;

	Collider playerCollider;

	Animation playerAnimation;
	TextureConfig animConfig;

	std::vector<KeyMapping> keyMappings;

	PState playerState;
	PState previousState;
	std::unordered_map<PState, sf::Texture*> stateTextures;
};

