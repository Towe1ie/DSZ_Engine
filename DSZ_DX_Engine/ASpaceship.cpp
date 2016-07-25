#include "ASpaceship.h"
#include "ResourceManager.h"
#include "BasicGeomentry.h"
#include <iostream>

Sprite* ASpaceship::spaceshipSprite = nullptr;

void OnBeginOverlap()
{
	std::cout << "BeginOverlap\n";
}

void OnEndOverlap()
{
	std::cout << "EndOverlap\n";
}

ASpaceship::ASpaceship()
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
	this->AttachComponent(circleComponent);
	circleComponent->rootComponent = sceneComponent;

	circleComponent->OnOverlapBegin = OnBeginOverlap;
	circleComponent->OnOverlapEnd = OnEndOverlap;
}

void ASpaceship::InitDefaults()
{

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
}

void ASpaceship::Render()
{
	DebugDrawCircle(circleComponent->GetWorldPosition(), circleComponent->radius, XMFLOAT4(1.f, 0.f, 0.f, 1.f), 16);
}
