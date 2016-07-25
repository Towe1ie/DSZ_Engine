#pragma once

enum class CollisionChannel { NONE, PLAYER, ENEMY };

enum class CollisionState { NONE, OVERLAPED };

struct CollisionCheckResult
{
	bool overlap;
};