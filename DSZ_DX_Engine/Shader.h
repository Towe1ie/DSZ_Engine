#pragma once

class Shader
{
public:
	virtual void Compile(const char* vs_fileName, const char* ps_fileName) = 0;
	virtual void Init() = 0;
	virtual void Activate() = 0;
	virtual void Clean() = 0;
	virtual void SetParameters() = 0;
	
protected:
	//virtual void CreateBuffers() = 0;
	//virtual void DestroyBuffers() = 0;
};