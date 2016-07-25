#pragma once

#include <DirectXMath.h>

enum MouseButton { LEFT = 0, MIDDLE, RIGHT };
enum class Key
{
	ESC = 0x1B, 
	LEFT = 0x25, UP, RIGHT, DOWN, 
	A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 
	F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

class Input
{
public:
	static void Update();

	static bool IsKeyDown(Key key);
	static bool IsButtonDown(MouseButton button);
	static bool IsKeyPressed(Key key);

	static DirectX::XMFLOAT2 SGetMousePos();
	static DirectX::XMFLOAT2 SGetMouseDelta();
	static DirectX::XMFLOAT2 WGetMousePos();
	static DirectX::XMFLOAT2 WGetMouseDelta();
	static float GetScrollDelta();

private:
	static void Initialize();
	static void KeyDown(unsigned int input);
	static void KeyUp(unsigned int input);
	static void ButtonDown(MouseButton button);
	static void ButtonUp(MouseButton button);

	static DirectX::XMFLOAT2 lastMouseCoord, currentMouseCoord;
	static float scrollValue;

private:
	static bool keys[256], last_keys[256];
	static bool mouseButtons[3];

private:
	Input();
	Input(const Input&);

	friend class EngineCore;
};