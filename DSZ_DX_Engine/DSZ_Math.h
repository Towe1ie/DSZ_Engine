#pragma once

#include <DirectXMath.h>

float Length(DirectX::XMFLOAT2);
float Length2(DirectX::XMFLOAT2);
DirectX::XMFLOAT2 Normalize(DirectX::XMFLOAT2);
bool NearlyEq(float f1, float f2, float aq);

DirectX::XMFLOAT2 operator-(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);

DirectX::XMFLOAT2 operator+(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);

DirectX::XMFLOAT2& operator+=(DirectX::XMFLOAT2 &v, float s);
DirectX::XMFLOAT2& operator+=(DirectX::XMFLOAT2 &v1, DirectX::XMFLOAT2 &v2);

DirectX::XMFLOAT2& operator-=(DirectX::XMFLOAT2 &v, float s);

DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v, float s);
DirectX::XMFLOAT2 operator*(float s, DirectX::XMFLOAT2 v);
DirectX::XMFLOAT2& operator*=(DirectX::XMFLOAT2 &v, float s);

DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2);

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v, float s);

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2);

float Lerp(float v0, float v1, float t);
DirectX::XMFLOAT2 VLerp(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2, float alpha);