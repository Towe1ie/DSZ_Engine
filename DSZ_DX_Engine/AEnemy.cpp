#include "AEnemy.h"
#include "BasicGeomentry.h"
#include "ShootableComponent.h"
#include <iostream>
#include "AProjectile.h"
#include "Camera.h"

void AEnemy::OnHit(AProjectile* projectile)
{
	std::cout << "I am " + Name + " and I am HIT!\n";
	this->Destroy();
	projectile->Destroy();
}

AEnemy::AEnemy(std::string name)
	: Actor(name)
{
	circleComponent = new CircleComponent();
	circleComponent->ChangeChannel(CollisionChannel::ENEMY);
	circleComponent->radius = 1.f;
	circleComponent->checkChannels[CollisionChannel::PLAYER] = true;
	circleComponent->rootComponent = sceneComponent;
	circleComponent->AttachTo(this);

	shootableComponent = new ShootableComponent();
	shootableComponent->OnHit = std::bind(&AEnemy::OnHit, this, std::placeholders::_1);
	shootableComponent->AttachTo(this);

	sceneComponent->position = XMFLOAT2(0.f, 5.f);
}

AEnemy::~AEnemy()
{
	shootableComponent->Destroy();
	circleComponent->Destroy();
}

void AEnemy::Render()
{
	DebugDrawCircle(circleComponent->GetWorldPosition(), circleComponent->radius, XMFLOAT4(0.0f, 0.f, 1.f, 1.f), 10);
}

void AEnemy::Update(GameTime& gameTime)
{
	
}