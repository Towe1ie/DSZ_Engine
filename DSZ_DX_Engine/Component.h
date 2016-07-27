#pragma once

class Actor;

class Component
{
public:
	Actor* GetOwner() { return owner; };
	void AttachTo(Actor* owner);

	virtual ~Component() { UnRegisterComponent(); };

	template<class T>
	static T* Create()
	{
		T* component = new T();
		return component;
	}

	void Destroy()
	{
		UnRegisterComponent();
		delete this;
	}
	
protected:
	virtual void RegisterComponent() { };
	virtual void UnRegisterComponent() { };

	

protected:
	Actor* owner = nullptr;

	friend class Actor;
};