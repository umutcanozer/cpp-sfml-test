#include "PlayerTest.h"

PlayerTest::PlayerTest(float movementSpeed, float jumpForce) :
	playerCollider(playerSprite)
{
	SetTexture();

    keyMappings = {
        {sf::Keyboard::Key::A, -1.f},
        {sf::Keyboard::Key::D, 1.f}
    };

	playerState = PState::Idle;
	previousState = PState::Idle;
	this->movementSpeed = movementSpeed;
	this->jumpForce = jumpForce;
	faceRight = true;
	canJump = true;

	currentTexture = &idleTexture;

	//imageCount, switchTime, width, height, xOffset, yOffset, gap 
	animConfig = { 10, 0.1f, 24.f, 40.f, 42.f, 0.f, 120.f};
	playerAnimation.SetTexture(currentTexture, animConfig);
	

	playerSprite.setTexture(*currentTexture);
	//left top width height
	playerSprite.setTextureRect(playerAnimation.textureRect);
	playerSprite.setOrigin(playerSprite.getGlobalBounds().width / 2, playerSprite.getGlobalBounds().height / 2);
	playerSprite.setPosition({ 0.f, 100.f });

}


void PlayerTest::Update(float deltaTime)
{
    velocity.x *= 0.f;
    for (KeyMapping& dir : keyMappings) {
        if (sf::Keyboard::isKeyPressed(dir.key)) {
			velocity.x += dir.direction;

			faceRight = velocity.x > 0.f;
        }
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.f * 981.f * jumpForce);
	}

	velocity.y += 981.f * deltaTime;

	if (velocity.x != 0.f) {
		velocity.x *= movementSpeed;
		playerState = PState::Walk;
	}
	else {
		playerState = PState::Idle;
	}
	
	if (playerState != previousState) {
		previousState = playerState;
		currentTexture = stateTextures[playerState];

		if (playerState == PState::Walk) {
			animConfig = { 10, 0.1f, 26.f, 40.f, 42.f, 0.f, 120.f };
		}
		else if (playerState == PState::Idle) {
			animConfig = { 10, 0.1f, 24.f, 40.f, 42.f, 0.f, 120.f };  
		}

		playerSprite.setTexture(*currentTexture);
		playerAnimation.SetTexture(currentTexture, animConfig);
	}


	playerAnimation.Update(deltaTime, faceRight);
	playerSprite.setTextureRect(playerAnimation.textureRect);
    playerSprite.move(velocity * deltaTime);
}

void PlayerTest::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.f) {
		velocity.x = 0.f;
	}
	else if (direction.x > 0.f) {
		velocity.x = 0.f;
	}
	if (direction.y < 0.f) {
		velocity.y = 0.f;
		canJump = true;
	}
	else if (direction.y > 0.f) {
		velocity.y = 0.f;
	}
}


void PlayerTest::Draw(sf::RenderWindow& window)
{
	window.draw(playerSprite);
    window.draw(test);
}

void PlayerTest::SetTexture()
{
    idleTexture.loadFromFile("soldier_sprites/_Idle.png");
    walkTexture.loadFromFile("soldier_sprites/_Run.png");

	stateTextures[PState::Idle] = &idleTexture;
	stateTextures[PState::Walk] = &walkTexture;
}

std::string PlayerTest::GetPlayerState()
{
	switch (playerState) {
	case PState::Idle: return "Idle";
	case PState::Walk: return "Walk";
	default: return "Unknown";
	}
}

PlayerTest::~PlayerTest()
{
}
