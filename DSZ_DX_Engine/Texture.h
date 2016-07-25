#pragma once

class Texture
{
public:
	virtual ~Texture() = 0 { }
	virtual void Load(const char* fileName) = 0;

};