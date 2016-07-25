#pragma once

#include <vector>
#include <stdlib.h>
#include "SceneComponent.h"
#include "SpriteComponent.h"
#include "Input.h"
#include "GameTime.h"

class Actor
{
public:
	SpriteComponent* spriteComponent;
	SceneComponent* sceneComponent;

	void AttachComponent(Component* component);

	Actor();

	void Spawn();
	virtual void Update(GameTime& gameTime);

private:
	bool defaultsInitialized;
	virtual void InitDefaults() { };
};