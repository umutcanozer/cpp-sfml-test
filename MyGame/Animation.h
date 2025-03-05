#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation();
	~Animation();

	void Update(float deltaTime, bool faceRight);
	void SetTexture(sf::Texture* texture, unsigned int imageCount, float switchTime);

public:
	sf::IntRect animRect;

private:
	unsigned int imageCount;
	unsigned int currentImage;
	
	float totalTime;
	float switchTime;

	sf::Texture* texture;
};

