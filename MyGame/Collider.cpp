#include "Collider.h"

Collider::Collider(sf::Sprite& col) :
	col(col)
{
}

bool Collider::CheckCollision(Collider& other, sf::Vector2f& direction, float force)
{
	/*
	* Imagine we have 2 rectangles. We need to check if they are colliding.
	* If they are not colliding then the gap between them is 0 or positive.
	* If they are colliding then the gap between them is negative.
	* If the distance between x cordinates of the rectangles is less than the sum of their half sizes then they are colliding
	* If the distance between y cordinates of the rectangles is less than the sum of their half sizes then they are colliding
	* If both of the above conditions are true then they are colliding.
	* If they are colliding then we need to push them back.
	*/

	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float xDistance = otherPosition.x - thisPosition.x;
	float yDistance = otherPosition.y - thisPosition.y;

	float gapX = abs(xDistance) - (otherHalfSize.x + thisHalfSize.x);
	float gapY = abs(yDistance) - (otherHalfSize.y + thisHalfSize.y);

	if (gapX < 0.f && gapY < 0.f) {
		force = std::min(std::max(force, 0.f), 1.f);
		if (gapX > gapY) {
			if (xDistance > 0) {
				Move(gapX * (1.f - force), 0.f);
				other.Move(-gapX * force, 0.f);

				direction.x = 1.f;
				direction.y = 0.f;
			}
			else {
				Move(-gapX * (1.f - force), 0.f);
				other.Move(gapX * force, 0.f);

				direction.x = -1.f;
				direction.y = 0.f;
			}
		}
		else {
			if (yDistance > 0) {
				Move(0.f, gapY * (1.f - force));
				other.Move(0.f, -gapY * force);

				direction.x = 0.f;
				direction.y = 1.f;
			}
			else {
				Move(0.f, -gapY * (1.f - force));
				other.Move(0.f, gapY * force);

				direction.x = 0.f;
				direction.y = -1.f;
			}
		}
		return true;
	}

	return false;
}

Collider::~Collider()
{
	
}

