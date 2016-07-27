#include "SpriteComponent.h"

void SpriteComponent::RegisterComponent()
{
	Renderer::spriteComponents.push_back(this);
}

void SpriteComponent::UnRegisterComponent()
{
	auto it = std::find(Renderer::spriteComponents.begin(), Renderer::spriteComponents.end(), this);
	Renderer::spriteComponents.erase(it);
}