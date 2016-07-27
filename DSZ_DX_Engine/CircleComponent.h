#pragma once

#include "ShapeComponent.h"

class CircleComponent : public ShapeComponent
{
public:
	float radius;

public:
	CircleComponent(SceneComponent* root = nullptr) : ShapeComponent(root) { }

	float GetRadiusScaled()
	{
		return max(GetWorldScale().x, GetWorldScale().y) * radius;
	}
};