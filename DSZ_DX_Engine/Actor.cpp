#include "Actor.h"
#include "SceneComponent.h"
#include "SpriteComponent.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Level.h"
#include "World.h"
#include "EngineCore.h"
#include "AIController.h"

using namespace DirectX;

Actor::Actor(std::string name)
	: Name(name)
{
	sceneComponent = new SceneComponent();
	spriteComponent = new SpriteComponent(Sprite::defaultSprite);
	sceneComponent->AttachTo(this);
	spriteComponent->AttachTo(this);
	rootComponent = sceneComponent;
	spriteComponent->rootComponent = sceneComponent;
	
}

Actor::~Actor()
{
	spriteComponent->Destroy();
	sceneComponent->Destroy();
	
}

void Actor::Destroy()
{
	bPendingDestroy = true;
	spriteComponent->bRender = false;
	bDoUpdate = false;
	bAlive = false;

	if (myController != nullptr)
		myController->Unposses();
}

void Actor::Update(GameTime& gameTime)
{
}

bool Actor::HasTag(std::string tag)
{
	return std::find(Tags.begin(), Tags.end(), tag) != Tags.end();
}