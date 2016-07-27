#include "Component.h"
#include "Actor.h"


void Component::AttachTo(Actor* owner)
{
	this->owner = owner;
	this->RegisterComponent();
	owner->components.push_back(this);
}
