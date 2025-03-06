#include "Player.h"

Player::Player(float movementSpeed)
{
    SetTextures();
    stateTextures[PlayerState::Idle] = &idleTexture;
    stateTextures[PlayerState::Walk] = &walkTexture;

    keyMappings = {
        {sf::Keyboard::Key::A, {-1.f, 0.f}},
        {sf::Keyboard::Key::D, {1.f, 0.f}},
        {sf::Keyboard::Key::W, {0.f, -1.f}},
        {sf::Keyboard::Key::S, {0.f, 1.f}}
    };

    playerState = PlayerState::Idle;
    currentTexture = *stateTextures[playerState];
    playerAnimation.SetTexture(&currentTexture, 10, 0.2f);

    this->movementSpeed = movementSpeed;
    faceRight = true;

    body.setSize(sf::Vector2f(60.f, 40.f));
    body.setScale({ 2.f, 2.f });
    body.setPosition({ 100.f, 100.f });
    body.setTexture(&currentTexture);
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 1);

    previousState = PlayerState::Idle;
}



void Player::Update(float deltaTime)
{
#pragma region movement
    sf::Vector2f movement(0.f, 0.f);
    for (const auto& key : keyMappings) {
        if (sf::Keyboard::isKeyPressed(key.key)) {
            movement += key.direction;

            if (movement.x > 0.f)
                faceRight = true;
            else
                faceRight = false;
        }
    }

   
    float magnitude = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (magnitude != 0.f) {
        movement /= magnitude;
        movement *= movementSpeed * deltaTime;
        body.move(movement);
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
#pragma endregion
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
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

