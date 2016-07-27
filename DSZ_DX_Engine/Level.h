#pragma once

#include <vector>


class GameTime;
class Actor;
class Camera;

class Level
{
private:
	std::vector<Actor*> actors;
	std::vector<Actor*> actorsToSpawn;
	std::vector<Camera*> cameras;
	
	
	void Update(GameTime& gameTime);
	void CleanActors();

	friend class World;

public:
	void AddActor(Actor* actor);
	void AddCamera(Camera* camera);

	template <class T>
	std::vector<T*> GetAllActorsOfClass()
	{
		std::vector<T*> retVector;
		auto it = actors.begin();

		for (; it != actors.end(); it++)
		{
			T* actor = dynamic_cast<T*>(*(it));
			if (actor != nullptr)
			{
				retVector.push_back(actor);
			}
		}

		return retVector;
	}

	Camera* currentCamera;

	friend class Renderer;
};