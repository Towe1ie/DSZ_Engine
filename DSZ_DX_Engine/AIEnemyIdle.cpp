#include "AIEnemyIdle.h"
#include "GameTime.h"
#include "DSZ_Math.h"
#include "AIStateMachine.h"
#include <iostream>
#include "ASpaceship.h"

using namespace DirectX;

class ASpaceship;

void AIEnemyIdle::Enter()
{
	std::cout << "Idle enter\n";
}

void AIEnemyIdle::Exit()
{
	std::cout << "Idle exit\n";
}

void AIEnemyIdle::Update(GameTime& gameTime)
{
	std::vector<ASpaceship*> spaceships = World::GetCurrentLevel()->GetAllActorsOfClass<ASpaceship>();
	Actor* spaceship = (Actor*)spaceships[0];
	Actor* myActor = MyActor();
	MyActor()->sceneComponent->position.y -= (float)gameTime.dt();

	if (Length2(myActor->sceneComponent->position - spaceship->sceneComponent->position) < 25.f)
	{
		myStateMachine->ChangeState("flee");
	}
}

void AIEnemyFlee::Enter()
{
	std::cout << "Flee enter\n";
}

void AIEnemyFlee::Exit()
{
	std::cout << "Flee exit\n";
}

void AIEnemyFlee::Update(GameTime& gameTime)
{
	std::vector<ASpaceship*> spaceships = World::GetCurrentLevel()->GetAllActorsOfClass<ASpaceship>();
	Actor* spaceship = (Actor*)spaceships[0];
	Actor* myActor = MyActor();

	XMFLOAT2 poteg = Normalize(myActor->sceneComponent->position - spaceship->sceneComponent->position);

	myActor->sceneComponent->position += poteg * (float)gameTime.dt() * 5;

	if (Length2(myActor->sceneComponent->position - spaceship->sceneComponent->position) > 50.f)
	{
		myStateMachine->ChangeState("idle");
	}
}