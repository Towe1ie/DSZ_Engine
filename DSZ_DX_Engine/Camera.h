#pragma once

#include <DirectXMath.h>

class GameTime;

class Camera
{
public:
	Camera(float aspectRatio);

	DirectX::XMFLOAT2 position;
	DirectX::XMMATRIX GetViewMatrix();

	void SetWidth(float w);
	void SetHeight(float h);

	float GetWidth();
	float GetHeight();

	void Update(GameTime& gameTime);

public:
	float DragSpeed = 0.01f;

	DirectX::XMFLOAT2 WorldToView(DirectX::XMFLOAT2 worldVec);

private:
	float aspectRatio;
	DirectX::XMFLOAT2 viewportSize;
};