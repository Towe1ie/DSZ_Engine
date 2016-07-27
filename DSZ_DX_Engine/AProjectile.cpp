#include "AProjectile.h"
#include "ResourceManager.h"
#include "DSZ_Math.h"
#include "BasicGeomentry.h"
#include <iostream>
#include "ShootableComponent.h"
#include "DSZ_Math.h"

AProjectile::AProjectile(std::string name)
	: Actor(name)
{
	ResourceManager::LoadPNGTexture("Resources\\ball.png", "projectile1");
	this->spriteComponent->sprite = new Sprite(ResourceManager::GetTexture("projectile1"));

	circleComponent = new CircleComponent(sceneComponent);
	circleComponent->radius = 0.5f;
	circleComponent->ChangeChannel(CollisionChannel::PLAYER);
	circleComponent->checkChannels[CollisionChannel::ENEMY] = true;
	circleComponent->OnOverlapBegin = std::bind(&AProjectile::OnOverlapBegin, this, std::placeholders::_1);
	circleComponent->AttachTo(this);

	sceneComponent->scale *= 0.2f;

	Tags.push_back("Projectile");
}

AProjectile::~AProjectile()
{
	circleComponent->Destroy();
}

void AProjectile::Update(GameTime &gameTime)
{
	sceneComponent->position += (float)gameTime.dt() * Direction * Speed;
}

void AProjectile::Render()
{
	DebugDrawCircle(circleComponent->GetWorldPosition(), circleComponent->GetRadiusScaled(), XMFLOAT4(1.f, 0.5f, 0.2f, 1.f), 20);
}

void AProjectile::OnOverlapBegin(ShapeComponent* other)
{
	ShootableComponent* sc = other->GetOwner()->GetComponent<ShootableComponent>();
	if (sc != nullptr && sc->OnHit != nullptr)
	{
		sc->OnHit(this);
	}
}