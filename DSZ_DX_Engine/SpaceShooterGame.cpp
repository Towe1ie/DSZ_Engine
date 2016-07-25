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

using namespace std;
using namespace DirectX;

static ASpaceship* actor;
static AEnemy* enemy;
//static AProjectile* projectile;

void SpaceShooterGame::LoadContent()
{
	actor = new ASpaceship();
	actor->Spawn();

	enemy = new AEnemy();
	enemy->Spawn();

	//projectile = new AProjectile();
	//projectile->Spawn();
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
	actor->Render();
	enemy->Render();
}