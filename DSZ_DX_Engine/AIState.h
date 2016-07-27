#pragma once

#include "Actor.h"

class GameTime;

class AIState
{
protected:
	class AIStateMachine* myStateMachine;

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(GameTime& gameTime) = 0;

	class Actor* MyActor();

	friend class AIStateMachine;
};