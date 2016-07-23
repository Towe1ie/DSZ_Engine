#pragma once

#include <Windows.h>

enum class GraphicsAPI_Type { D3D11 };

class GraphicsAPI
{
public:
	virtual void Create(HWND hwnd) = 0;
	virtual void Destroy() = 0;
	//virtual void Render() = 0;
	virtual void* GetDevice() = 0;
	virtual void* GetDeviceContext() = 0;

	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
};