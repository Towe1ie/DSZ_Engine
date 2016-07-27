#pragma once

#include "SceneComponent.h"
#include "BasicPhysics.h"
#include <map>
#include <functional>

class ShapeComponent : public SceneComponent
{
private:
	CollisionChannel myChannel;
	CollisionState collisionState = CollisionState::NONE;

public:
	ShapeComponent(SceneComponent* root = nullptr);

	bool ChecksCollision(CollisionChannel channel);

	void ChangeChannel(CollisionChannel channel);

	std::function<void(ShapeComponent*)> OnOverlapBegin = nullptr;
	std::function<void()> OnOverlapEnd = nullptr;

public:
	std::map<CollisionChannel, bool> checkChannels;

protected:
	virtual void RegisterComponent() override;
	virtual void UnRegisterComponent() override;

	friend class PhysicsManager;
};