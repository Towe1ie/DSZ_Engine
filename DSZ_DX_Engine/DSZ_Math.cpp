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

XMFLOAT2& operator-=(XMFLOAT2 &v, float s)
{
	return v += (-s);
}

DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v, float s)
{
	return XMFLOAT2(v.x * s, v.y * s);
}

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v, float s)
{
	return XMFLOAT3(v.x * s, v.y * s, v.z * s);
}