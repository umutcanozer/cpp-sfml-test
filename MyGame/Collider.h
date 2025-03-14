#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::Sprite& col);
	~Collider();

	void Move(float dx, float dy) { col.move(dx, dy); }

	bool CheckCollision(Collider& other, sf::Vector2f& direction, float force);
	sf::Vector2f GetPosition() { return col.getPosition(); };
	sf::Vector2f GetHalfSize() {
		return sf::Vector2f(col.getGlobalBounds().width / 2.f, col.getGlobalBounds().height / 2.f);
	};

private:
	sf::Sprite& col;


};


