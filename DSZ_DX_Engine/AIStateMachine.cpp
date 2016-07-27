#include "AIStateMachine.h"
#include "AIState.h"

void AIStateMachine::ChangeState(std::string newState)
{
	if (currentState != nullptr)
	{
		currentState->Exit();
	}

	currentState = states[newState];

	if (currentState != nullptr)
	{
		currentState->Enter();
	}
}

void AIStateMachine::Update(GameTime& gameTime)
{
	if (currentState != nullptr)
		currentState->Update(gameTime);
}

void AIStateMachine::AddState(AIState* state, std::string stateName)
{
	states[stateName] = state;
	state->myStateMachine = this;
}