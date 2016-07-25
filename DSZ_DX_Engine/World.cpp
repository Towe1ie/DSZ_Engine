#include "World.h"

std::vector<Level*> World::levels;
Level* World::currentLevel;

Level* World::CreateNewLevel()
{
	Level* newLevel = new Level();
	levels.push_back(newLevel);

	return newLevel;
}
void World::SetCurrentLevel(Level* level)
{
	currentLevel = level;
}

void World::Update(GameTime& gameTime)
{
	currentLevel->Update(gameTime);
}

Level* World::GetCurrentLevel()
{
	return currentLevel;
}