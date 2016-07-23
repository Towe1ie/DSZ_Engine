#include "SpaceShooterGame.h"
#include <iostream>
#include "PNG_Texture.h"
#include "Sprite.h"
#include "EngineCore.h"

using namespace std;
using namespace DirectX;

static PNG_Texture* spaceshipTex;
static Sprite* spaceshipSprite;

void SpaceShooterGame::LoadContent()
{
	spaceshipTex = new PNG_Texture();
	spaceshipTex->Load("Resources\\spaceship.png");
	spaceshipSprite = new Sprite(spaceshipTex);
	spaceshipSprite->pos = XMFLOAT3(0.f, 0.f, 0.f);
}

void SpaceShooterGame::UnloadContent()
{
	delete spaceshipSprite;
	delete spaceshipTex;
}

void SpaceShooterGame::Update(GameTime& gameTime)
{
	spaceshipSprite->pos.y += gameTime.dt() * 1;
	cout << spaceshipSprite->pos.y << endl;
}
void SpaceShooterGame::Render()
{
	spaceshipSprite->Render();
	
}