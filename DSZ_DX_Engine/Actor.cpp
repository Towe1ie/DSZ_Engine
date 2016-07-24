#include "Actor.h"

Actor* Actor::objects = nullptr;
int Actor::objects_size = 0;
int Actor::objects_last = 0;

Actor** Actor::pointers = nullptr;
int Actor::pointers_size = 0;
int Actor::pointers_last = 0;

int Actor::last_free_pointer = -1;