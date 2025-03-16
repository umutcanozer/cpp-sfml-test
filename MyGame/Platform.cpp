#include "Platform.h"


sf::Texture Platform::platformTexture;

Platform::Platform(sf::Vector2f pos) :
    platformCollider(platformSprite)
{
    platformTexture.loadFromFile("assets/platform_sprites/platform.png");
    platformSprite.setTexture(platformTexture);

    platformRect.width = platformTexture.getSize().x;
    platformRect.height = platformTexture.getSize().y;
    platformSprite.setTextureRect(platformRect);
	platformSprite.setOrigin(platformRect.width / 2, platformRect.height / 2);
    platformSprite.setPosition(pos);
	platformSprite.setScale(0.75f, 0.75f);
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(platformSprite);
}

Platform::~Platform()
{
}

