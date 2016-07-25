#include "Actor.h"
#include "SceneComponent.h"
#include "SpriteComponent.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Level.h"
#include "World.h"
#include "EngineCore.h"

using namespace DirectX;

Actor::Actor()
{
	sceneComponent = new SceneComponent();
	spriteComponent = new SpriteComponent(Sprite::defaultSprite);
	this->AttachComponent(sceneComponent);
	this->AttachComponent(spriteComponent);
	
}

void Actor::Spawn()
{
	World::GetCurrentLevel()->AddActor(this);
}

void Actor::AttachComponent(Component* component)
{
	component->owner = this;
	component->RegisterComponent();
}

void Actor::Update(GameTime& gameTime)
{
}