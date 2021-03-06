#include "ShapeComponent.h"
#include "PhysicsManager.h"
#include <algorithm>

ShapeComponent::ShapeComponent(SceneComponent* root)
	: SceneComponent(root)
{
	
}

void ShapeComponent::ChangeChannel(CollisionChannel channel)
{
	// Remove from old channel
	std::vector<ShapeComponent*> shapes = PhysicsManager::collisionChannels[myChannel];
	std::vector<ShapeComponent*>::iterator begin = shapes.begin(), end = shapes.end();
	shapes.erase(std::remove(begin, end, this), shapes.end());
	
	// Add to new channel
	PhysicsManager::collisionChannels[channel].push_back(this);
	myChannel = channel;
}

void ShapeComponent::RegisterComponent()
{
	if (myChannel != CollisionChannel::NONE)
	{
		if (std::find(PhysicsManager::collisionChannels[myChannel].begin(), PhysicsManager::collisionChannels[myChannel].end(), this) == PhysicsManager::collisionChannels[myChannel].end())
		{
			PhysicsManager::collisionChannels[myChannel].push_back(this);
		}
	}
}

void ShapeComponent::UnRegisterComponent()
{

	auto begin = PhysicsManager::collisionChannels[myChannel].begin();
	auto end = PhysicsManager::collisionChannels[myChannel].end();
	auto it = std::find(begin, end, this);
	if (it != end)
		PhysicsManager::collisionChannels[myChannel].erase(it);
}

bool ShapeComponent::ChecksCollision(CollisionChannel channel)
{
	if (checkChannels.find(channel) == checkChannels.end())
		return false;
	return checkChannels[channel];
}