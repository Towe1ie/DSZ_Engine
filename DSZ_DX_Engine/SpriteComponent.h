#pragma once

#include "Component.h"
#include "Renderer.h"

class Sprite;

class SpriteComponent : public Component
{
public:
	SpriteComponent(Sprite* sprite = nullptr) : sprite(sprite) { }
	Sprite* sprite = nullptr;

	virtual void RegisterComponent() override;
};