#pragma once

#include "AIState.h"

class AIEnemyIdle : public AIState
{
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(class GameTime& gameTime) override;
};

class AIEnemyFlee : public AIState
{
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(class GameTime& gameTime) override;
};