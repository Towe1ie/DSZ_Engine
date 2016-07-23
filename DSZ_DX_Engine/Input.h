#pragma once

#include <DirectXMath.h>

enum MouseButton { LEFT = 0, MIDDLE, RIGHT };

class Input
{
public:
	static void Update();

	static bool IsKeyDown(unsigned int);
	static bool IsButtonDown(MouseButton button);

	static DirectX::XMFLOAT2 SGetMousePos();
	static DirectX::XMFLOAT2 SGetMouseDelta();
	static DirectX::XMFLOAT2 WGetMousePos();
	static DirectX::XMFLOAT2 WGetMouseDelta();
	static float GetScrollDelta();

private:
	static void Initialize();
	static void KeyDown(unsigned int);
	static void KeyUp(unsigned int);
	static void ButtonDown(MouseButton button);
	static void ButtonUp(MouseButton button);

	static DirectX::XMFLOAT2 lastMouseCoord, currentMouseCoord;
	static float scrollValue;

private:
	static bool keys[256];
	static bool mouseButtons[3];

private:
	Input();
	Input(const Input&);
	~Input();

	friend class EngineCore;
};