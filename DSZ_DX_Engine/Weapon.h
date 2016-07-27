#pragma once

class AProjectile;
class ShootingComponent;
class ProjectileFactory;

class Weapon
{
public:
	float Frequency = 1.0f;
	float Range = 1.0f;
	bool bCanShoot = true;

public:
	Weapon(ShootingComponent* myShootingComponent = nullptr) : myShootingComponent(myShootingComponent) { }
	virtual void Shoot() = 0;

	ProjectileFactory* projectileFactory = nullptr;
protected:
	ShootingComponent* myShootingComponent = nullptr;
};