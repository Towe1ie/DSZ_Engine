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
		/*const Actor* owner = (*it)->GetOwner();
		SceneComponent* sc = owner->sceneComponent;*/
		(*it)->sprite->Render((*it)->GetWorldPosition(), (*it)->GetWorldRotation() , (*it)->GetWorldScale());
	}
}