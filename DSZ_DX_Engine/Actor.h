#pragma once

#include <vector>
#include <stdlib.h>
#include "SP.h"

class Actor
{
private:
	static Actor* objects;
	static int objects_size, objects_last;
	static Actor** pointers;
	static int pointers_size, pointers_last;
	static int last_free_pointer;

	static void* operator new(std::size_t size)
	{
		if (objects_last == objects_size)
		{
			objects_size = objects_size == 0 ? 1 : objects_size * 2;
			
			objects = (Actor*)realloc(objects, objects_size * sizeof(Actor));
		}
		int objects_index = objects_last++;

		int pointers_index = -1;
		if (last_free_pointer != -1)
		{
			pointers_index = last_free_pointer;
			last_free_pointer = (int)(long long)pointers[last_free_pointer];
		}

		if (pointers_index == -1)
		{
			if (pointers_last == pointers_size)
			{
				pointers_size = pointers_size == 0 ? 1 : pointers_size * 2;
				pointers = (Actor**)realloc(pointers, pointers_size * sizeof(Actor*));
			}

			pointers_index = pointers_last++;
		}

		Actor* new_space = objects + objects_index;
		::new (new_space) Actor();
		pointers[pointers_index] = new_space;

		new_space->pointers_index = pointers_index;
		new_space->objects_index = objects_index;

		return new_space;
	}

	static void operator delete(void* ptr, std::size_t size)
	{
		Actor* actor = (Actor*)ptr;
		int oi = actor->objects_index;
		int pi = actor->pointers_index;
		actor->~Actor();

		pointers[pi] = (Actor*)((long long)last_free_pointer);
		last_free_pointer = pi;

		objects[oi] = std::move(objects[--objects_last]);
		objects[oi].objects_index = oi;
		pointers[objects[oi].pointers_index] = objects + oi;
	}

	int pointers_index, objects_index;

	template<class T>
	friend SP<T> CreateObject();
	template<class T>
	friend void DestroyObject(SP<T> sp);
	friend class SP<Actor>;

	Actor::Actor()
	{

	}
public:

	int i;
	double d;
};