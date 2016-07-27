#include "ASpaceship.h"
#include "ResourceManager.h"
#include "BasicGeomentry.h"
#include "ShootingComponent.h"
#include "Weapons.h"
#include <iostream>
#include "AProjectile.h"
#include "Camera.h"
#include "DSZ_Math.h"

Sprite* ASpaceship::spaceshipSprite = nullptr;



ASpaceship::ASpaceship(std::string name)
	: Actor(name)
{
	if (spaceshipSprite == nullptr)
	{
		ResourceManager::LoadPNGTexture("Resources\\spaceship.png", "spaceship");
		spaceshipSprite = new Sprite(ResourceManager::GetTexture("spaceship"));
	}

	spriteComponent->sprite = spaceshipSprite;

	circleComponent = new CircleComponent();
	circleComponent->ChangeChannel(CollisionChannel::PLAYER);
	circleComponent->radius = 1.f;
	circleComponent->checkChannels[CollisionChannel::ENEMY] = true;
	circleComponent->rootComponent = sceneComponent;
	circleComponent->OnOverlapBegin = std::bind(&ASpaceship::OnHit, this, std::placeholders::_1);
	circleComponent->AttachTo(this);
	
	shootingComponent = new ShootingComponent();

	BasicRifle* basicRifle = new BasicRifle(shootingComponent);
	DoubleBasicRifle* doubleBasicRifle = new DoubleBasicRifle(shootingComponent);
	BasicProjectileFactory* fac = new BasicProjectileFactory();

	basicRifle->projectileFactory = fac;
	doubleBasicRifle->projectileFactory = fac;
	shootingComponent->weapons["BasicRifle"] = basicRifle;
	shootingComponent->weapons["DoubleBasicRifle"] = doubleBasicRifle;
	shootingComponent->SetCurrentWeapon("DoubleBasicRifle");

	shootingComponent->AttachTo(this);
}

ASpaceship::~ASpaceship()
{
	circleComponent->Destroy();
	shootingComponent->Destroy();
}

void ASpaceship::Update(GameTime& gameTime)
{
	if (Input::IsKeyDown(Key::UP))
	{
		sceneComponent->position.y += (float)gameTime.dt() * speed;
	}
	if (Input::IsKeyDown(Key::DOWN))
	{
		sceneComponent->position.y -= (float)gameTime.dt() * speed;
	}
	if (Input::IsKeyDown(Key::LEFT))
	{
		sceneComponent->position.x -= (float)gameTime.dt() * speed;
	}
	if (Input::IsKeyDown(Key::RIGHT))
	{
		sceneComponent->position.x += (float)gameTime.dt() * speed;
	}

	if (Input::IsKeyDown(Key::SPACE))
		shootingComponent->TryShoot();

}

void ASpaceship::Render()
{
	DebugDrawCircle(circleComponent->GetWorldPosition(), circleComponent->radius, XMFLOAT4(1.f, 0.f, 0.f, 1.f), 16);
}

void ASpaceship::OnHit(ShapeComponent* other)
{
	std::cout << "UMRI!\n";
}