#include "Weapons.h"
#include "AProjectile.h"
#include "ShootingComponent.h"
#include "DSZ_Math.h"
#include "Task.h"
#include <iostream>

using namespace DirectX;

void BasicRifle::Shoot()
{
	if (projectileFactory != nullptr)
	{
		AProjectile* projectile = this->projectileFactory->MakeProjectile();
		projectile->sceneComponent->position = myShootingComponent->GetOwner()->sceneComponent->GetWorldPosition();
		projectile->Speed = 10.f;
		projectile->Direction = XMFLOAT2(0.f, 1.f);
		this->bCanShoot = false;

		Task* t = new Task();
		t->delay = this->Frequency;
		t->func = [this]() { this->bCanShoot = true; };
		t->Fire();
	}
}

void DoubleBasicRifle::Shoot()
{
	if (projectileFactory != nullptr)
	{
		AProjectile* projectile1 = this->projectileFactory->MakeProjectile();
		projectile1->sceneComponent->position = myShootingComponent->GetOwner()->sceneComponent->GetWorldPosition() + XMFLOAT2(0.3f, 0.0f);
		projectile1->Speed = 10.f;
		projectile1->Direction = XMFLOAT2(0.f, 1.f);

		AProjectile* projectile2 = this->projectileFactory->MakeProjectile();
		projectile2->sceneComponent->position = myShootingComponent->GetOwner()->sceneComponent->GetWorldPosition() - XMFLOAT2(0.3f, 0.0f);
		projectile2->Speed = 10.f;
		projectile2->Direction = XMFLOAT2(0.f, 1.f);

		this->bCanShoot = false;

		Task* t = new Task();
		t->delay = this->Frequency;
		t->func = [this]() { this->bCanShoot = true; };
		t->Fire();
	}
}