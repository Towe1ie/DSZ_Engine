#pragma once

class Actor;
class AIStateMachine;
class GameTime;

#include <vector>

class AIController
{
public:
	void Posses(Actor* actor);
	void Unposses();
	void SetStateMachine(AIStateMachine* stateMachine);
	void RegisterController() { controllers.push_back(this); }

private:
	static std::vector<AIController*> controllers;
	static void UpdateAllControllers(GameTime& gameTime);

	Actor* actor = nullptr;
	AIStateMachine* stateMachine = nullptr;

	void Update(GameTime& gameTime);

	friend class AIStateMachine;
	friend class AIState;
	friend class EngineCore;
};