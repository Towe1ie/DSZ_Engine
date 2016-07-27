#include "SpaceShooterGame.h"
#include <iostream>
#include "PNG_Texture.h"
#include "Sprite.h"
#include "EngineCore.h"
#include "ASpaceship.h"
#include "SpriteComponent.h"
#include "SceneComponent.h"
#include "AEnemy.h"
#include "Globals.h"
#include "AProjectile.h"
#include "ShootableComponent.h"
#include "ResourceManager.h"
#include "AI.h"

using namespace std;
using namespace DirectX;

static ASpaceship* spaceship;
static AEnemy* enemy;
static Actor* starfield;

void SpaceShooterGame::LoadContent()
{
	ResourceManager::LoadPNGTexture("Resources\\starfield.png", "starfield");

	starfield = Actor::Spawn<Actor>("Starfield");
	starfield->spriteComponent->sprite = new Sprite(ResourceManager::GetTexture("starfield"));
	starfield->sceneComponent->scale.x = 30;
	starfield->sceneComponent->scale.y = 15;

	spaceship = Actor::Spawn<ASpaceship>("Spaceship");

	enemy = Actor::Spawn<AEnemy>("Enemy1");

	AIEnemyIdle* enemyIdle = new AIEnemyIdle();
	AIEnemyFlee* enemyFlee = new AIEnemyFlee();

	AIStateMachine* enemyStateMachine = new AIStateMachine();
	enemyStateMachine->AddState(enemyIdle, "idle");
	enemyStateMachine->AddState(enemyFlee, "flee");
	enemyStateMachine->ChangeState("idle");

	AIController* enemyController = new AIController();
	enemyController->SetStateMachine(enemyStateMachine);
	enemyController->Posses(enemy);
	enemyController->RegisterController();

}

void SpaceShooterGame::UnloadContent()
{
}

void SpaceShooterGame::Update(GameTime& gameTime)
{
	if (Input::IsKeyPressed(Key::F11))
		EngineCore::GetGraphicsAPI()->SetFullScreen(currFullscreen = !currFullscreen);
}
void SpaceShooterGame::Render()
{
}