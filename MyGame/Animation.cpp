#include "Animation.h"

Animation::Animation()
{
}

void Animation::SetTexture(sf::Texture* texture, const TextureConfig& config) {
	this->imageCount = config.imageCount;
	this->switchTime = config.switchTime;
	this->xOffset = config.xOffset;
	this->yOffset = config.yOffset;
	this->gap = config.gap;

	totalTime = 0.f;
	currentImage = 0;

	textureRect.width = config.width;
	textureRect.height = config.height;
}

void Animation::Update(float deltaTime, bool faceRight)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage++;

		if (currentImage >= imageCount) currentImage = 0;
	}

	textureRect.top = 0;

	if (faceRight) {
		textureRect.left = xOffset + (currentImage * gap);
		textureRect.width = abs(textureRect.width);
	}
	else {
		textureRect.left = xOffset + ((currentImage) * gap) - textureRect.width;
		textureRect.width = -abs(textureRect.width);
	}

}

Animation::~Animation()
{
}
