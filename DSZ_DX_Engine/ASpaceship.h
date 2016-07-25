#pragma once

#include "Actor.h"
#include "Sprite.h"
#include "CircleComponent.h"

class ASpaceship : public Actor
{
public:
	ASpaceship();
	virtual void Update(GameTime& gameTime) override;
	virtual void InitDefaults() override;

	float speed = 10.0f;

	void Render();

protected:
	CircleComponent* circleComponent;

	static Sprite* spaceshipSprite;

};