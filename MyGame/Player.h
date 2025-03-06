#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <unordered_map>


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
private:
	float movementSpeed;
	sf::RectangleShape body;

	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture currentTexture;

	Animation playerAnimation;
	bool faceRight;

	struct KeyMapping {
		sf::Keyboard::Key key;
		sf::Vector2f direction;
	};
	std::vector<KeyMapping> keyMappings;

	PlayerState playerState;
	PlayerState previousState;
	std::unordered_map<PlayerState, sf::Texture*> stateTextures;
};

