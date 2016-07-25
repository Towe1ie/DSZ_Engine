#include "Level.h"


void Level::Update(GameTime& gameTime)
{
	std::vector<Actor*>::iterator it = actors.begin();

	currentCamera->Update(gameTime);

	for (it; it != actors.end(); it++)
	{
		(*it)->Update(gameTime);
	}
}

void Level::AddActor(Actor* actor)
{
	actors.push_back(actor);
}

void Level::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
}