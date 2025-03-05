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
	Player(sf::Texture* idleTexture, sf::Texture* walkTexture, unsigned int imageCount, float switchTime, float movementSpeed);
	~Player();
	
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	float movementSpeed;
	sf::RectangleShape body;
	sf::Texture currentTexture;

	Animation playerAnimation;
	bool faceRight;

	struct KeyMapping {
		sf::Keyboard::Key key;
		sf::Vector2f direction;
	};
	std::vector<KeyMapping> keyMappings;

	PlayerState playerState;
	std::unordered_map<PlayerState, sf::Texture*> stateTextures;
};

