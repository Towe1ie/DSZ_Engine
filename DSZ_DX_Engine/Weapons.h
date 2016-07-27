#pragma once

#include "Weapon.h"

class BasicRifle : public Weapon
{
public:
	BasicRifle(ShootingComponent* myShootingComponent) : Weapon(myShootingComponent) { this->Frequency = 0.1f; }

	virtual void Shoot() override;
};

class DoubleBasicRifle : public Weapon
{
public:
	DoubleBasicRifle(ShootingComponent* myShootingComponent) : Weapon(myShootingComponent) { this->Frequency = 0.05f; }

	virtual void Shoot() override;
};