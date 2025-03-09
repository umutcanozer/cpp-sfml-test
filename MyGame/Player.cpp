#include "Player.h"

Player::Player(float movementSpeed, float jumpHeight) :
    playerCollider(body)
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
    playerAnimation.SetTexture(&currentTexture, 10, 0.2f);

	this->jumpHeight = jumpHeight;
    this->movementSpeed = movementSpeed;
    faceRight = true;
	canJump = true;
    
	body.setSize({ 80.f, 100.f });
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
    body.setPosition({ 0.f, 0.f });
    body.setTexture(&currentTexture);

    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(2.f);

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
        body.setTexture(&currentTexture);
        playerAnimation.SetTexture(stateTextures[playerState], 10, 0.1f);
        previousState = playerState;
    }

    playerAnimation.Update(deltaTime, faceRight);
    body.setTextureRect(playerAnimation.animRect);
    body.move(velocity * deltaTime);
#pragma endregion
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
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
