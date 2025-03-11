#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::Sprite& spriteColl);
	~Collider();

	void Move(float dx, float dy) { spriteColl.move(dx, dy); }

	bool CheckCollision(Collider& other, sf::Vector2f& direction, float force);
	sf::Vector2f GetPosition() { return spriteColl.getPosition(); };
	sf::Vector2f GetHalfSize() {
		return sf::Vector2f(spriteColl.getGlobalBounds().width / 2.0f,
			spriteColl.getGlobalBounds().height / 2.0f);
	};

private:
	sf::Sprite& spriteColl;


};


