#include "Task.h"
#include <stdio.h>
#include "GameTime.h"

std::list<Task*> Task::tasks;

void Task::Fire()
{
	float totalTime = 0.f;

	auto it = tasks.begin();
	while (it != tasks.end() && this->delay > (totalTime + (*it)->timeRemaining))
	{
		totalTime += (*it)->timeRemaining;
	}

	this->timeRemaining = this->delay - totalTime;
	if (it != tasks.end())
		(*it)->timeRemaining -= this->timeRemaining;
	tasks.insert(it, this);
}

void Task::Update(GameTime& gameTime)
{
	float dt = (float)gameTime.dt();
	auto it = tasks.begin();
	if (it != tasks.end())
	{
		(*it)->timeRemaining -= dt;
		while (it != tasks.end() && (*it)->timeRemaining <= 0.f + 0.001f)
		{
			Task *task = (*it);
			task->func();
			delete task;
			tasks.pop_front();
			it = tasks.begin();
		}
	}
}