#pragma once

#include <vector>
class Actor;
class SpriteComponent;

class Renderer
{
public:
	static std::vector<SpriteComponent*> spriteComponents;

	static void Render();
};