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
	Player(float movementSpeed);
	~Player();
	
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void SetTextures();

	std::string GetPlayerState();
	sf::Vector2f GetPosition() { return body.getPosition(); };
	sf::RectangleShape GetBody() { return body; };
	Collider& GetCollider() { return playerCollider; };
private:
	float movementSpeed;
	sf::RectangleShape body;

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

