#include "Level.h"
#include "Camera.h"
#include "Actor.h"
#include <iterator>
#include <algorithm>

void Level::Update(GameTime& gameTime)
{
	CleanActors();
	std::move(actorsToSpawn.begin(), actorsToSpawn.end(), std::back_inserter(actors));
	actorsToSpawn.erase(actorsToSpawn.begin(), actorsToSpawn.end());
	auto it = actors.begin();

	currentCamera->Update(gameTime);

	for (it; it != actors.end(); it++)
	{
		if ((*it)->bDoUpdate && (*it)->bAlive)
			(*it)->Update(gameTime);
	}
}

void Level::CleanActors()
{
	for (auto it = actors.begin(); it != actors.end(); it++)
	{
		if ((*it)->IsPendingDestroy())
		{
			delete *it;
		}
	}

	auto new_end = std::remove_if(
		actors.begin(),
		actors.end(),
		[](Actor* a) { return a->IsPendingDestroy(); }
	);


	actors.erase(new_end, actors.end());
}

void Level::AddActor(Actor* actor)
{
	actorsToSpawn.push_back(actor);
}

void Level::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
}

