#include "Camera.h"
#include "Input.h"
#include <Windows.h>
#include "EngineCore.h"
#include "BasicGeomentry.h"

using namespace DirectX;

Camera::Camera(float aspectRatio)
	: position(0.f, 0.f), aspectRatio(aspectRatio)
{

}

XMMATRIX Camera::GetViewMatrix()
{
	XMMATRIX mat = XMMatrixIdentity();
	mat = XMMatrixTranspose(XMMatrixTranslation(-position.x, -position.y, 0.0f) * XMMatrixScaling(2.f / viewportSize.x, 2.f / viewportSize.y, 1.0f));
	return mat;
}

void Camera::Update(GameTime& gameTime)
{
	if (Input::IsButtonDown(LEFT))
	{
		if (Input::IsKeyDown(VK_UP))
			position.y += 0.0001f;

		if (Input::IsKeyDown(VK_DOWN))
			position.y -= 0.0001f;

		if (Input::IsKeyDown(VK_RIGHT))
			position.x += 0.0001f;

		if (Input::IsKeyDown(VK_LEFT))
			position.x -= 0.0001f;

		position.x -= Input::WGetMouseDelta().x;
		position.y += Input::WGetMouseDelta().y;
	}

	SetWidth(viewportSize.x - Input::GetScrollDelta() * 0.01f);
}
void Camera::SetWidth(float w)
{
	viewportSize = XMFLOAT2(w, w / aspectRatio);
}

void Camera::SetHeight(float h)
{
	viewportSize = XMFLOAT2(h * aspectRatio, h);
}

float Camera::GetWidth()
{
	return viewportSize.x;
}

float Camera::GetHeight()
{
	return viewportSize.y;
}

DirectX::XMFLOAT2 Camera::WorldToView(DirectX::XMFLOAT2 worldVec)
{
	XMFLOAT2 normVec = XMFLOAT2(worldVec.x / EngineCore::GetRes_x(), worldVec.y / EngineCore::GetRes_y());
	normVec.x -= 0.5f;

	return XMFLOAT2(normVec.x * GetWidth(), normVec.y * GetHeight()) + position;
}
