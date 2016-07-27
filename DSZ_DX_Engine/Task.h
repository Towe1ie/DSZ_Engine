#pragma once

#include <functional>
#include <list>

class GameTime;

class Task
{
public:
	std::function<void(void)> func;
	float delay;
	float timeRemaining;
	void Fire();
private:
	static std::list<Task*> tasks;
	static void Update(GameTime& gameTime);

	friend class EngineCore;
};