#pragma once

#include "Actor.h"
#include "CircleComponent.h"

class AProjectile : public Actor
{
public:
	float Speed = 1.f;
	float Damage = 0.f;
	DirectX::XMFLOAT2 Direction = DirectX::XMFLOAT2(0.0f, 1.0f);

	CircleComponent* circleComponent = nullptr;

public:
	AProjectile(std::string name);
	virtual ~AProjectile();

	void OnOverlapBegin(ShapeComponent* other);

	virtual void Update(GameTime &gameTime) override;
	virtual void Render() override;
};

class ProjectileFactory
{
public:
	float Damage = 10.f;
	virtual AProjectile* MakeProjectile() = 0;
};

class BasicProjectileFactory : public ProjectileFactory
{
public:
	float Damage = 10.f;
	virtual AProjectile* MakeProjectile()
	{
		AProjectile* pr = Actor::Spawn<AProjectile>("Projectile");
		pr->Damage = Damage;
		return pr;
	}
};