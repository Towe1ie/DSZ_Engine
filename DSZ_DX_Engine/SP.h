#pragma once


template <class T>
class SP
{
private:
	int pointers_index;

	T* GetRawPointer()
	{
		return T::pointers[pointers_index];
	}
public:
	SP(int pointers_index)
	{
		this->pointers_index = pointers_index;
	}

	T& operator*()
	{
		return *(T::pointers[pointers_index]);
	}

	T* operator->()
	{
		return GetRawPointer();
	}

	template<class T>
	friend SP<T> CreateObject();
	template<class T>
	friend void DestroyObject(SP<T> sp);

};

template<class T>
SP<T> CreateObject()
{
	T* o = new T();
	return SP<T>(o->pointers_index);
}

template<class T>
void DestroyObject(SP<T> sp)
{
	delete T::pointers[sp.pointers_index];
}