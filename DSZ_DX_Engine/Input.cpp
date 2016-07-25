#include "Input.h"
#include <string.h>
#include <Windows.h>
#include "EngineCore.h"
#include "Camera.h"
#include "DSZ_Math.h"
#include "World.h"

using namespace DirectX;



bool Input::keys[256];
bool Input::last_keys[256];
bool Input::mouseButtons[3];
XMFLOAT2 Input::lastMouseCoord = XMFLOAT2(0.f, 0.f);
XMFLOAT2 Input::currentMouseCoord = XMFLOAT2(0.f, 0.f);
float Input::scrollValue = 0.0f;

void Input::Initialize()
{
	memset(keys, false, sizeof(keys));
	memset(last_keys, false, sizeof(last_keys));
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

bool Input::IsKeyDown(Key key)
{
	return keys[(int)key];
}

bool Input::IsKeyPressed(Key key)
{
	return (keys[(int)key] == false && last_keys[(int)key] == true);
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
	memcpy(last_keys, keys, 256 * sizeof(bool));

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
	Camera* cam = World::GetCurrentLevel()->currentCamera;
	return cam->WorldToView(currentMouseCoord);
}

DirectX::XMFLOAT2 Input::WGetMouseDelta()
{
	Camera* cam = World::GetCurrentLevel()->currentCamera;
	return cam->WorldToView(currentMouseCoord) - cam->WorldToView(lastMouseCoord);
}

float Input::GetScrollDelta()
{
	return scrollValue;
}