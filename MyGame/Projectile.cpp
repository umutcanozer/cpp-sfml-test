#include "Projectile.h"

sf::Texture Projectile::projectileTexture;

Projectile::Projectile(float movementSpeed, sf::Vector2f pos) :
	projectileCol(projectileSprite)
{
	this->movementSpeed = movementSpeed;
	velocity = { movementSpeed, 0.f };
	faceRight = true;

	//imageCount, switchTime, width, height, xOffset, yOffset, gap 
	animConfig = { 5, 0.1f, 32.f, 32.f, 0.f, 0.f, 32.f };
	projectileAnim.SetTexture(&projectileTexture, animConfig);

	projectileTexture.loadFromFile("assets/projectile2.png");
	projectileSprite.setTexture(projectileTexture);
	projectileSprite.setTextureRect(projectileAnim.textureRect);
	projectileSprite.setOrigin(projectileSprite.getGlobalBounds().width / 2, projectileSprite.getGlobalBounds().height / 2);
	projectileSprite.setPosition({ pos });
}

void Projectile::Update(float deltaTime)
{
	projectileSprite.move(deltaTime * velocity);
	projectileAnim.Update(deltaTime, faceRight);
	projectileSprite.setTextureRect(projectileAnim.textureRect);
	projectileCol.UpdatePosition(projectileSprite.getPosition());
}

void Projectile::Draw(sf::RenderWindow& window)
{
	window.draw(projectileSprite);
}

Projectile::~Projectile()
{
}
