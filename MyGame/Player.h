#pragma once
#include "SFML/Graphics.hpp"

class Player
{
public:
	Player(sf::Texture* texture, float movementSpeed);
	~Player();
	
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	float movementSpeed;
	sf::RectangleShape body;

	struct KeyMapping {
		sf::Keyboard::Key key;
		sf::Vector2f direction;
	};
	std::vector<KeyMapping> keyMappings;
};

