#include "DSZ_Math.h"

using namespace DirectX;

float Length(DirectX::XMFLOAT2 v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

float Length2(DirectX::XMFLOAT2 v)
{
	return v.x*v.x + v.y*v.y;
}

DirectX::XMFLOAT2 Normalize(DirectX::XMFLOAT2 v)
{
	float len = Length(v);
	if (len == 0.f)
	{
		return XMFLOAT2(0.f, 0.f);
	}
	else
	{
		return XMFLOAT2(v.x / len, v.y / len);
	}
}

bool NearlyEq(float f1, float f2, float aq)
{
	return (fabs(f1 - f2) < aq);
}

XMFLOAT2 operator-(XMFLOAT2 v1, XMFLOAT2 v2)
{
	return XMFLOAT2(v1.x - v2.x, v1.y - v2.y);
}

XMFLOAT2 operator+(XMFLOAT2 v1, XMFLOAT2 v2)
{
	return XMFLOAT2(v1.x + v2.x, v1.y + v2.y);
}

XMFLOAT2& operator+=(XMFLOAT2 &v, float s)
{
	v.x += s;
	v.y += s;
	return v;
}

DirectX::XMFLOAT2& operator+=(DirectX::XMFLOAT2 &v1, DirectX::XMFLOAT2 &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

XMFLOAT2& operator-=(XMFLOAT2 &v, float s)
{
	return v += (-s);
}

DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v, float s)
{
	return XMFLOAT2(v.x * s, v.y * s);
}

DirectX::XMFLOAT2 operator*(float s, DirectX::XMFLOAT2 v)
{
	return v * s;
}

DirectX::XMFLOAT2& operator*=(DirectX::XMFLOAT2& v, float s)
{
	v = v * s;
	return v;
}

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v, float s)
{
	return XMFLOAT3(v.x * s, v.y * s, v.z * s);
}

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2)
{
	return XMFLOAT3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{
	return XMFLOAT2(v1.x * v2.x, v1.y * v2.y);
}

float Lerp(float v0, float v1, float t)
{
	return v0 + t*(v1 - v0);
}

DirectX::XMFLOAT2 VLerp(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2, float alpha)
{
	return v1 + alpha*(v1 - v2);
}