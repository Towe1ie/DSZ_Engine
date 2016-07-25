#pragma once

#include "SceneComponent.h"
#include "BasicPhysics.h"
#include <map>

class ShapeComponent : public SceneComponent
{
private:
	CollisionChannel myChannel;
	CollisionState collisionState = CollisionState::NONE;

public:
	ShapeComponent();

	bool ChecksCollision(CollisionChannel channel);

	void ChangeChannel(CollisionChannel channel);
	void (*OnOverlapBegin)(void) = nullptr;
	void (*OnOverlapEnd)(void) = nullptr;

public:
	std::map<CollisionChannel, bool> checkChannels;

protected:
	virtual void RegisterComponent() override;

	friend class PhysicsManager;
};