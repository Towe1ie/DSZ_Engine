#pragma once

#include "Actor.h"
#include "CircleComponent.h"

class AEnemy : public Actor
{
public:
	CircleComponent* circleComponent;
	virtual void Update(GameTime& gameTime) override;

	void Render();

	AEnemy();
};