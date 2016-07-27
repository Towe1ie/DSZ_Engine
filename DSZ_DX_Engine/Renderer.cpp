#include "Renderer.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Sprite.h"
#include "SceneComponent.h"

using namespace std;

vector<SpriteComponent*> Renderer::spriteComponents;
typedef vector<SpriteComponent*>::iterator SpriteComponentIt;

void Renderer::Render()
{
	for (SpriteComponentIt it = spriteComponents.begin(); it != spriteComponents.end(); it++)
	{
		if ((*it)->bRender)
			(*it)->sprite->Render((*it)->GetWorldPosition(), (*it)->GetWorldRotation() , (*it)->GetWorldScale());
	}

	for (auto it = World::GetCurrentLevel()->actors.begin(); it != World::GetCurrentLevel()->actors.end(); it++)
	{
		(*it)->Render();
	}
}