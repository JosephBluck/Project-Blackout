#pragma once

#include "Sprite.h"

class FloatParticle
{
public:
	FloatParticle(Sprite* inputSprite, float x, float y, int w, int h, float _xSpeed, float _ySpeed, int _lifeSpan, int _fadeTime);
	~FloatParticle();

	void Update();

	bool isExpired = false;

private:
	Sprite* sprite = NULL;

	int lifeSpan, fadeTime, timer;
	float xPos, yPos, xSpeed, ySpeed, width, height, startHeight, startWidth;
	
};