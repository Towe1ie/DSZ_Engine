#pragma once

#include "SceneComponent.h"
#include "Renderer.h"

class Sprite;

class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent(Sprite* sprite = nullptr) : sprite(sprite) { }
	Sprite* sprite = nullptr;

	virtual void RegisterComponent() override;
};