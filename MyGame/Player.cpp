#include "Player.h"

Player::Player(float movementSpeed, float jumpForce) :
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


void Player::Update(float deltaTime)
{
    velocity.x *= 0.f;
    for (KeyMapping& dir : keyMappings) {
        if (sf::Keyboard::isKeyPressed(dir.key)) {
			velocity.x += dir.direction;

			faceRight = velocity.x > 0.f;
        }
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump) {
		playerState = PState::Jump;
		canJump = false;
		velocity.y = -sqrtf(2.f * 981.f * jumpForce);
	}

	velocity.y += 981.f * deltaTime;

	if (velocity.x != 0.f) {
		velocity.x *= movementSpeed;

		if (playerState != PState::Jump && playerState != PState::Fall) playerState = PState::Walk;
	}
	else {
		if (playerState != PState::Jump && playerState != PState::Fall) playerState = PState::Idle;
	}

	if (velocity.y > 100.f) playerState = PState::Fall;
	else if (velocity.y < 0.f) playerState = PState::Jump;
	
	if (playerState != previousState) {
		previousState = playerState;
		currentTexture = stateTextures[playerState];

		//imageCount, switchTime, width, height, xOffset, yOffset, gap 
		if (playerState == PState::Walk) {
			animConfig = { 10, 0.2f, 26.f, 40.f, 42.f, 0.f, 120.f };
		}
		else if (playerState == PState::Idle) {
			animConfig = { 10, 0.1f, 24.f, 40.f, 42.f, 0.f, 120.f };  
		}
		else if (playerState == PState::Jump) {
			animConfig = { 3, 0.1f, 27.f, 40.f, 42.f, 0.f, 120.f };
		}else if (playerState == PState::Fall) {
			animConfig = { 3, 0.1f, 34.f, 40.f, 37.f, 0.f, 120.f };
		}

		playerSprite.setTexture(*currentTexture);
		playerAnimation.SetTexture(currentTexture, animConfig);
	}


	playerAnimation.Update(deltaTime, faceRight);
	playerSprite.setTextureRect(playerAnimation.textureRect);
    playerSprite.move(velocity * deltaTime);
}

void Player::OnCollision(sf::Vector2f direction)
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
		playerState = PState::Idle;
	}
	else if (direction.y > 0.f) {
		velocity.y = 0.f;
	}
}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(playerSprite);
    window.draw(test);
}

void Player::SetTexture()
{
    idleTexture.loadFromFile("soldier_sprites/_Idle.png");
    walkTexture.loadFromFile("soldier_sprites/_Run.png");
	jumpTexture.loadFromFile("soldier_sprites/_Jump.png");
	fallTexture.loadFromFile("soldier_sprites/_Fall.png");

	stateTextures[PState::Idle] = &idleTexture;
	stateTextures[PState::Walk] = &walkTexture;
	stateTextures[PState::Jump] = &jumpTexture;
	stateTextures[PState::Fall] = &fallTexture;
}

std::string Player::GetPlayerState()
{
	switch (playerState) {
	case PState::Idle: return "Idle";
	case PState::Walk: return "Walk";
	case PState::Jump: return "Jump";
	case PState::Fall: return "Fall";
	default: return "Unknown";
	}
}

Player::~Player()
{
}
