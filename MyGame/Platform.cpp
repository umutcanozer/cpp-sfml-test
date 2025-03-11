#include "Platform.h"
#include <iostream>
Platform::Platform(sf::Texture& texture, sf::Vector2f pos) :
    platformCollider(spritePlatform)
{
    spritePlatform.setTexture(texture);

    platformRect.width = texture.getSize().x;
    platformRect.height = texture.getSize().y;
    spritePlatform.setTextureRect(platformRect);

    spritePlatform.setOrigin(platformRect.width / 2.0f, platformRect.height / 2.0f);
    spritePlatform.setPosition(pos);

    
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(spritePlatform);
}

Platform::~Platform()
{
}

