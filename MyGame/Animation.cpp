#include "Animation.h"

Animation::Animation()
{
}

void Animation::SetTexture(sf::Texture* texture, unsigned int imageCount, float switchTime) {
	this->texture = texture;
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0.f;
	currentImage = 0;

	animRect.width = texture->getSize().x / static_cast<float>(imageCount);
	animRect.height = texture->getSize().y;
}

void Animation::Update(float deltaTime, bool faceRight)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage++;
		
		if (currentImage >= imageCount) currentImage = 0;
	}

	animRect.top = 0; 

	if (faceRight) {
		animRect.left = currentImage * abs(animRect.width);
		animRect.width = abs(animRect.width);
	}
	else {
		animRect.left = (currentImage + 1) * abs(animRect.width);
		animRect.width = -abs(animRect.width);
	}
		
}

Animation::~Animation()
{
}

