#include "AIController.h"
#include "GameTime.h"
#include "AIStateMachine.h"
#include "Actor.h"

std::vector<AIController*> AIController::controllers;

void AIController::Update(GameTime& gameTime)
{
	if (stateMachine != nullptr && actor != nullptr)
	{
		stateMachine->Update(gameTime);
	}
}

void AIController::SetStateMachine(AIStateMachine* stateMachine)
{
	this->stateMachine = stateMachine;
	stateMachine->myController = this;
}

void AIController::Posses(Actor* actor)
{
	this->actor = actor;
	actor->myController = this;
}

void AIController::Unposses()
{
	actor->myController = nullptr;
	this->actor = nullptr;

}

void AIController::UpdateAllControllers(GameTime& gameTime)
{
	auto it = controllers.begin();

	for (; it != controllers.end(); it++)
	{
		(*it)->Update(gameTime);
	}
}