#pragma once
#include "SFML/Graphics.hpp"

struct TextureConfig {
	unsigned int imageCount;
	float switchTime;
	float width;
	float height;
	float xOffset;
	float yOffset;
	float gap;
};

class Animation
{
public:
	Animation();
	~Animation();

	void Update(float deltaTime, bool faceRight);
	void SetTexture(sf::Texture* texture, const TextureConfig& config);

public:
	sf::IntRect textureRect;

private:
	unsigned int imageCount;
	unsigned int currentImage;

	float totalTime;
	float switchTime;

	float xOffset;
	float yOffset;
	float gap;
};
