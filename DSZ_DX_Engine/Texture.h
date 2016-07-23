#pragma once

class Texture
{
public:
	virtual ~Texture() = 0 { }
	virtual void Load(char* fileName) = 0;

};