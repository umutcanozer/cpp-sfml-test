#include "Platform.h"
#include <iostream>
Platform::Platform(sf::Vector2f pos) :
    platformCollider(spritePlatform)
{
    platformTexture.loadFromFile("platform_sprites/box.png");
    spritePlatform.setTexture(platformTexture);

    platformRect.width = platformTexture.getSize().x;
    platformRect.height = platformTexture.getSize().y;
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

