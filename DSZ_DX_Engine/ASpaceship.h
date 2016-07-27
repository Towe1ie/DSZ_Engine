#pragma once

#include "Actor.h"
#include "Sprite.h"
#include "CircleComponent.h"

class ShootingComponent;

class ASpaceship : public Actor
{
public:
	ASpaceship(std::string name);
	
	virtual void Update(GameTime& gameTime) override;

	float speed = 10.0f;

	void Render();

protected:
	
	virtual ~ASpaceship();

	CircleComponent* circleComponent = nullptr;
	ShootingComponent* shootingComponent = nullptr;

	static Sprite* spaceshipSprite;

	void OnHit(ShapeComponent* other);
};