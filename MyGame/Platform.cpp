#include "Platform.h"

Platform::Platform(sf::Vector2f size, sf::Vector2f pos) :
	platformCollider(body)
{
    body.setSize(size);
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
    body.setPosition(pos);
    body.setTexture(nullptr);
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

Platform::~Platform()
{
}

