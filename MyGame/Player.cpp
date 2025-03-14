#include "Player.h"

Player::Player(float movementSpeed, float jumpHeight) :
    playerCollider(playerSprite)
{
    SetTextures();
    stateTextures[PlayerState::Idle] = &idleTexture;
    stateTextures[PlayerState::Walk] = &walkTexture;

    keyMappings = {
        {sf::Keyboard::Key::A, {-1.f, 0.f}},
        {sf::Keyboard::Key::D, {1.f, 0.f}}
        //{sf::Keyboard::Key::W, {0.f, -1.f}},
        //{sf::Keyboard::Key::S, {0.f, 1.f}}
    };

    playerState = PlayerState::Idle;
    currentTexture = *stateTextures[playerState];
    //playerAnimation.SetTexture(&currentTexture, 10, 0.2f);

	this->jumpHeight = jumpHeight;
    this->movementSpeed = movementSpeed;
    faceRight = true;
	canJump = true;
    

    playerSprite.setTexture(currentTexture);
    
    
    playerSprite.setPosition({ 0.f, 0.f });

    previousState = PlayerState::Idle;
}



void Player::Update(float deltaTime)
{
    velocity.x *= 0.f;
#pragma region movement
	
    for (auto& keyMapping : keyMappings) {
        if (sf::Keyboard::isKeyPressed(keyMapping.key)) {
            velocity.x += keyMapping.direction.x;
            faceRight = velocity.x > 0.f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump) {
        canJump = false;
        velocity.y = -sqrtf(2.f * 981.f * jumpHeight);
    }

	velocity.y += 981.f * deltaTime;

    if (velocity.x != 0.f) {
        velocity.x *= movementSpeed;
        playerState = PlayerState::Walk;
    }
    else {
        playerState = PlayerState::Idle;
    }

    if (playerState != previousState) {
        currentTexture = *stateTextures[playerState];
        playerSprite.setTexture(currentTexture);
        //playerAnimation.SetTexture(stateTextures[playerState], 10, 0.1f);
        previousState = playerState;
    }

    playerAnimation.Update(deltaTime, faceRight);
    playerSprite.setTextureRect(playerAnimation.textureRect);
    playerSprite.move(velocity * deltaTime);
#pragma endregion

    sf::FloatRect bounds = playerSprite.getGlobalBounds();

    hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
    hitbox.setPosition(bounds.left, bounds.top);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(2.f);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(playerSprite);
    window.draw(hitbox);
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
	}
	else if (direction.y > 0.f) {
		velocity.y = 0.f;
	}
}

void Player::SetTextures()
{
    idleTexture.loadFromFile("soldier_sprites/_Idle.png");
    walkTexture.loadFromFile("soldier_sprites/_Run.png");
}

std::string Player::GetPlayerState()
{
    switch (playerState) {
    case PlayerState::Idle: return "Idle";
    case PlayerState::Walk: return "Walk";
    default: return "Unknown";
    }
}

Player::~Player()
{
}
