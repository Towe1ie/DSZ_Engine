#pragma once

#include "Component.h"

class GameTime;

class ActorComponent : public Component
{
public:
	virtual void Update(GameTime& gameTime);
};