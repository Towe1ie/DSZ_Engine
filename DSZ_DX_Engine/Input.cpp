#include "Input.h"
#include <string.h>
#include <Windows.h>
#include "EngineCore.h"
#include "Camera.h"
#include "BasicGeomentry.h"

using namespace DirectX;



bool Input::keys[256];
bool Input::mouseButtons[3];
XMFLOAT2 Input::lastMouseCoord = XMFLOAT2(0.f, 0.f);
XMFLOAT2 Input::currentMouseCoord = XMFLOAT2(0.f, 0.f);
float Input::scrollValue = 0.0f;

void Input::Initialize()
{
	memset(keys, false, sizeof(keys));
	memset(mouseButtons, false, sizeof(mouseButtons));
}

void Input::KeyDown(unsigned int input)
{
	keys[input] = true;
}

void Input::KeyUp(unsigned int input)
{
	keys[input] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	return keys[key];
}

bool Input::IsButtonDown(MouseButton button)
{
	return mouseButtons[button];
}

void Input::ButtonDown(MouseButton button)
{
	mouseButtons[button] = true;
}

void Input::ButtonUp(MouseButton button)
{
	mouseButtons[button] = false;
}

void Input::Update()
{
	lastMouseCoord = currentMouseCoord;
	//scrollValue = 0.f;

	POINT p;
	GetCursorPos(&p);

	currentMouseCoord.x = (float)p.x;
	currentMouseCoord.y = (float)p.y;
}

DirectX::XMFLOAT2 Input::SGetMousePos()
{
	return currentMouseCoord;
}

DirectX::XMFLOAT2 Input::SGetMouseDelta()
{
	return currentMouseCoord - lastMouseCoord;
}

XMFLOAT2 Input::WGetMousePos()
{
	Camera* cam = EngineCore::GetCurrentCamera();
	return cam->WorldToView(currentMouseCoord);
}

DirectX::XMFLOAT2 Input::WGetMouseDelta()
{
	Camera* cam = EngineCore::GetCurrentCamera();
	return cam->WorldToView(currentMouseCoord) - cam->WorldToView(lastMouseCoord);
}

float Input::GetScrollDelta()
{
	return scrollValue;
}