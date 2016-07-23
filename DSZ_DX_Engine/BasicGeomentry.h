#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;
class HLSL_Shader;

struct Vertex
{
	Vertex(XMFLOAT3 pos = XMFLOAT3(), XMFLOAT4 color = XMFLOAT4());
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct Triangle
{
	Triangle();

	Vertex v1, v2, v3;

	ID3D11Buffer* pVBuffer;

	void Render();
};

void DebugDrawLine(XMFLOAT2 v1, XMFLOAT2 v2, XMFLOAT4 color);

extern HLSL_Shader* shader;

XMFLOAT2 operator-(XMFLOAT2 v1, XMFLOAT2 v2);

XMFLOAT2 operator+(XMFLOAT2 v1, XMFLOAT2 v2);

XMFLOAT2& operator+=(XMFLOAT2 &v, float s);

XMFLOAT2& operator-=(XMFLOAT2 &v, float s);