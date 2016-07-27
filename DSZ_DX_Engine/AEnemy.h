#pragma once

#include "Actor.h"
#include "CircleComponent.h"

class ShootableComponent;
class AProjectile;

class AEnemy : public Actor
{
public:
	CircleComponent* circleComponent;
	ShootableComponent* shootableComponent;

	void OnHit(AProjectile* projectile);

	virtual void Update(GameTime& gameTime) override;

	void Render();

	AEnemy(std::string name = "UnnamedEnemy");
	virtual ~AEnemy();
};