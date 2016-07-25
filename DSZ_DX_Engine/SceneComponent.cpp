#include "SceneComponent.h"
#include "DSZ_Math.h"

using namespace DirectX;

XMFLOAT2 SceneComponent::GetWorldPosition()
{
	if (rootComponent != nullptr)
	{
		return rootComponent->GetWorldPosition() + this->position;
	}
	else
	{
		return this->position;
	}
}

DirectX::XMFLOAT2 SceneComponent::GetWorldRotation()
{
	if (rootComponent != nullptr)
	{
		return rootComponent->GetWorldRotation() + this->rotation;
	}
	else
	{
		return this->rotation;
	}
}
DirectX::XMFLOAT2 SceneComponent::GetWorldScale()
{
	if (rootComponent != nullptr)
	{
		return rootComponent->GetWorldScale() * this->scale;
	}
	else
	{
		return this->scale;
	}
}