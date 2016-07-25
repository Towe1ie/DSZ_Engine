#include "SpaceShooterGame.h"
#include <iostream>
#include "PNG_Texture.h"
#include "Sprite.h"
#include "EngineCore.h"
#include "ASpaceship.h"
#include "SpriteComponent.h"
#include "SceneComponent.h"
#include "AEnemy.h"

using namespace std;
using namespace DirectX;


static ASpaceship* actor;
static AEnemy* enemy;

void SpaceShooterGame::LoadContent()
{
	actor = new ASpaceship();
	actor->Spawn();

	enemy = new AEnemy();
	enemy->Spawn();
}

void SpaceShooterGame::UnloadContent()
{

}

void SpaceShooterGame::Update(GameTime& gameTime)
{

}
void SpaceShooterGame::Render()
{
	actor->Render();
	enemy->Render();
}