#include "SpriteComponent.h"

void SpriteComponent::RegisterComponent()
{
	Renderer::spriteComponents.push_back(this);
}