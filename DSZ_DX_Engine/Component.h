#pragma once

class Actor;

class Component
{
public:
	const Actor* GetOwner() const { return owner; };
	
protected:
	virtual void RegisterComponent() { };

protected:
	Actor* owner = nullptr;

	friend class Actor;
};