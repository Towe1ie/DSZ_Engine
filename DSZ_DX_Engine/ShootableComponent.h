#pragma once

#include "Component.h"
#include <functional>

class AProjectile;

class ShootableComponent : public Component
{
public:
	std::function<void(AProjectile*)> OnHit = nullptr;
};