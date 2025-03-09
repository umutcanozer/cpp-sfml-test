#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include "Animation.h"
#include "Collider.h"


enum class PlayerState {
	Idle,
	Walk
};

class Player
{
public:
	Player(float movementSpeed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	void SetTextures();

	std::string GetPlayerState();
	sf::Vector2f GetPosition() { return body.getPosition(); };
	sf::RectangleShape GetBody() { return body; };
	float GetPlayerVelocityX() { return velocity.x; };
	float GetPlayerVelocityY() { return velocity.y; };
	Collider& GetCollider() { return playerCollider; };
private:
	float movementSpeed;
	float jumpHeight;
	bool canJump;

	sf::RectangleShape body;
	sf::Vector2f velocity;

	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture currentTexture;

	Animation playerAnimation;
	bool faceRight;

	Collider playerCollider;

	struct KeyMapping {
		sf::Keyboard::Key key;
		sf::Vector2f direction;
	};
	std::vector<KeyMapping> keyMappings;

	PlayerState playerState;
	PlayerState previousState;
	std::unordered_map<PlayerState, sf::Texture*> stateTextures;
};
