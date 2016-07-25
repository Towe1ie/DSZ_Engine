#pragma once

#include <Windows.h>

class GameTime
{
public:
	double dt();

private:
	LARGE_INTEGER currentTime;
	LARGE_INTEGER lastUpdateTime;

	LARGE_INTEGER clock;

private:
	GameTime();
	friend class EngineCore;
};