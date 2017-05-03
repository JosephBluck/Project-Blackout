#include "FloatingParticle.h"

FloatParticle::FloatParticle(Sprite* inputSprite, float x, float y, int w, int h, float _xSpeed, float _ySpeed, int _lifeSpan, int _fadeTime)
{
	//Set up the parameters
	sprite = inputSprite;
	isExpired = false;

	xPos = x;
	yPos = y;
	width = w;
	height = h;
	startWidth = width;
	startHeight = height;

	xSpeed = _xSpeed;
	ySpeed = _ySpeed;
	lifeSpan = _lifeSpan;
	fadeTime = _fadeTime;

	timer = 0;
}

FloatParticle::~FloatParticle()
{

}

void FloatParticle::Update()
{
	timer++;

	if (!isExpired){ //Check for expiration before update
		if (timer >= lifeSpan + fadeTime) isExpired = true;

		xPos += xSpeed;
		yPos += ySpeed;

		if (timer < lifeSpan) {
			sprite->SetSize(width, height);
			sprite->Draw(xPos, yPos);
		}
		else if (timer < lifeSpan + fadeTime) {
			width = startWidth - ((startWidth / fadeTime) * (timer - lifeSpan));
			height = startHeight - ((startHeight / fadeTime) * (timer - lifeSpan));
			yPos += (startHeight / fadeTime) / 2;
			xPos += (startWidth / fadeTime) / 2;

			sprite->SetSize(width, height);
			sprite->Draw(xPos, yPos);
		}

	}
}