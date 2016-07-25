#pragma once

#include <vector>
#include <map>
#include "GameTime.h"
#include "ShapeComponent.h"
#include "BasicPhysics.h"


class CircleComponent;

class PhysicsManager
{
private:
	typedef std::map<CollisionChannel, std::vector<ShapeComponent*>> t_collisionChannels;
	static std::map<CollisionChannel, std::vector<ShapeComponent*>> collisionChannels;

	static CollisionCheckResult CheckCollision(CircleComponent* c1, CircleComponent* c2);

	static void Update(GameTime& gameTime);

	friend class ShapeComponent;
	friend class EngineCore;
};