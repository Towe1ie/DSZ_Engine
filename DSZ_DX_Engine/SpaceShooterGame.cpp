#include "SpaceShooterGame.h"
#include <iostream>
#include "PNG_Texture.h"
#include "Sprite.h"
#include "EngineCore.h"
#include "Actor.h"

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

	SP<Actor> actor1 = CreateObject<Actor>();
	actor1->d = 1.0f;
	SP<Actor> actor2 = CreateObject<Actor>();
	actor2->d = 2.0f;
	SP<Actor> actor3 = CreateObject<Actor>();
	actor3->d = 3.0f;
	SP<Actor> actor4 = CreateObject<Actor>();
	actor4->d = 4.0f;

	DestroyObject(actor1);
	DestroyObject(actor2);

	SP<Actor> actor5 = CreateObject<Actor>();
	actor5->d = 5.0f;
	SP<Actor> actor6 = CreateObject<Actor>();
	actor6->d = 6.0f;
}

void SpaceShooterGame::UnloadContent()
{
	delete spaceshipSprite;
	delete spaceshipTex;
}

void SpaceShooterGame::Update(GameTime& gameTime)
{
	spaceshipSprite->pos.y += (float)gameTime.dt() * 1;
	cout << spaceshipSprite->pos.y << endl;
}
void SpaceShooterGame::Render()
{
	spaceshipSprite->Render();
	
}