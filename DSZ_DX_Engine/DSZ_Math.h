#pragma once

#include <DirectXMath.h>

float Length(DirectX::XMFLOAT2);
float Length2(DirectX::XMFLOAT2);

DirectX::XMFLOAT2 operator-(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);

DirectX::XMFLOAT2 operator+(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);

DirectX::XMFLOAT2& operator+=(DirectX::XMFLOAT2 &v, float s);

DirectX::XMFLOAT2& operator-=(DirectX::XMFLOAT2 &v, float s);

DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v, float s);

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v, float s);