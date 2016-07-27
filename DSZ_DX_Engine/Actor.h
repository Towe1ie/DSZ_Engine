#pragma once

#include <vector>
#include <stdlib.h>
#include "SceneComponent.h"
#include "SpriteComponent.h"
#include "Input.h"
#include "GameTime.h"
#include <string>
#include "World.h"
#include "Level.h"

class Actor
{
public:
	SceneComponent* rootComponent = nullptr;
	SpriteComponent* spriteComponent;
	SceneComponent* sceneComponent;

	std::vector<std::string> Tags;
	std::string Name;

public:

	template <class T>
	static T* Spawn(std::string name)
	{
		T* actor = new T(name);
		if (actor != nullptr)
		{
			World::GetCurrentLevel()->AddActor(actor);
			actor->bAlive = true;
		}

		return actor;
	}

	void Destroy();
	bool IsPendingDestroy() { return bPendingDestroy; }

	virtual void Update(GameTime& gameTime);
	virtual void Render() { };

	bool HasTag(std::string tag);

	template <class T>
	T* GetComponent()
	{
		std::vector<Component*>::iterator it;

		for (it = components.begin(); it != components.end(); it++)
		{
			if (T* t = dynamic_cast<T*>(*(it)))
			{
				return t;
			}
		}

		return nullptr;
	}

protected:
	Actor(std::string name = "UnnamedActor");
	virtual ~Actor();

	std::vector<Component*> components;
	bool bPendingDestroy = false;
	bool bAlive = false;
	bool bDoUpdate = true;

private:
	class AIController *myController = nullptr;

	friend class Level;
	friend class Component;
	friend class AIController;
};