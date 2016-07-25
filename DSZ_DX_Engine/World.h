#pragma once

#include "Level.h"
#include <vector>
class GameTime;

class World
{
private:
	static std::vector<Level*> levels;
	static Level* currentLevel;

	static void Update(GameTime& gameTime);


public:
	static Level* CreateNewLevel();
	static void SetCurrentLevel(Level* level);
	static Level* GetCurrentLevel();

	friend class EngineCore;
};