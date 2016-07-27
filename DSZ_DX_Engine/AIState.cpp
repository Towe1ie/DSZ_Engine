#include "AIState.h"
#include "AIStateMachine.h"
#include "AIController.h"

Actor* AIState::MyActor()
{
	return this->myStateMachine->myController->actor;
}