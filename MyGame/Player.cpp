#include "Player.h"

Player::Player(sf::Texture* texture, float movementSpeed)
{
    keyMappings = {
        {sf::Keyboard::Key::A, {-1.f, 0.f}},
        {sf::Keyboard::Key::D, {1.f, 0.f}},
        {sf::Keyboard::Key::W, {0.f, -1.f}},
        {sf::Keyboard::Key::S, {0.f, 1.f}}
    };

    this->movementSpeed = movementSpeed;

    body.setSize(sf::Vector2f(100.f, 150.f));
    body.setPosition({ 100.f, 100.f });
    body.setTexture(texture);
}

void Player::Update(float deltaTime)
{
#pragma region movement
    sf::Vector2f movement(0.f, 0.f);
    for (const auto& key : keyMappings) {
        if (sf::Keyboard::isKeyPressed(key.key)) {
            movement += key.direction;
        }
    }

    float magnitude = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (magnitude != 0.f) {
        movement /= magnitude;
        movement *= movementSpeed * deltaTime;
        body.move(movement);
    }
#pragma endregion
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}


Player::~Player()
{
}

