#pragma once

#include "SceneComponent.h"
#include "Renderer.h"
#include "Sprite.h"

class Sprite;

class SpriteComponent : public SceneComponent
{
public:
	bool bRender = true;
public:
	SpriteComponent(Sprite* sprite = nullptr) : sprite(sprite) { }
	Sprite* sprite = nullptr;

	virtual void RegisterComponent() override;
	virtual void UnRegisterComponent() override;
};