#pragma once

#include <map>
#include <string>

class AIState;

class AIStateMachine
{
public:
	void AddState(AIState* state, std::string stateName);
	void ChangeState(std::string newState);

private:
	class AIController* myController = nullptr;

	std::map<std::string, AIState*> states;
	AIState* currentState = nullptr;
	
	void Update(class GameTime& gameTime);

	friend class AIController;
	friend class AIState;
};