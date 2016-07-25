#pragma once

#include <vector>
#include "Actor.h"
#include "Camera.h"

class GameTime;

class Level
{
private:
	std::vector<Actor*> actors;
	std::vector<Camera*> cameras;
	
	
	void Update(GameTime& gameTime);

	friend class World;

public:
	void AddActor(Actor* actor);
	void AddCamera(Camera* camera);

	Camera* currentCamera;

};