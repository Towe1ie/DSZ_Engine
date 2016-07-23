#include "BasicGeomentry.h"
#include "EngineCore.h"
#include "GraphicsAPI.h"
#include "HLSL_Shader.h"

HLSL_Shader* shader;

Vertex::Vertex(XMFLOAT3 pos, XMFLOAT4 color)
{
	this->pos = pos;
	this->color = color;
}

Triangle::Triangle()
{
	v1.pos.x = 1.0f;
	v1.pos.y = -1.0f;
	v1.pos.z = 0.0f;
	v1.color.x = 1.0f;
	v1.color.y = 0.0f;
	v1.color.z = 0.0f;
	v1.color.w = 1.0f;

	v2.pos.x = -1.0f;
	v2.pos.y = -1.0f;
	v2.pos.z = 0.0f;
	v2.color.x = 0.0f;
	v2.color.y = 1.0f;
	v2.color.z = 0.0f;
	v2.color.w = 1.0f;

	v3.pos.x = 0.0f;
	v3.pos.y = 1.0f;
	v3.pos.z = 0.0f;
	v3.color.x = 0.0f;
	v3.color.y = 0.0f;
	v3.color.z = 1.0f;
	v3.color.w = 1.0f;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	ID3D11Device *dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();
	ID3D11DeviceContext *devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	dev->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &v1, sizeof(Vertex) * 3);
	devcon->Unmap(pVBuffer, NULL);
}

void Triangle::Render()
{
	shader->Activate();

	ID3D11DeviceContext *devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcon->Draw(3, 0);
}

void DebugDrawLine(XMFLOAT2 v1, XMFLOAT2 v2, XMFLOAT4 color)
{
	Vertex buff[2];
	buff[0].pos.x = v1.x;
	buff[0].pos.y = v1.y;
	buff[0].pos.z = 0.0f;

	buff[0].color = color;

	buff[1].pos.x = v2.x;
	buff[1].pos.y = v2.y;
	buff[1].pos.z = 0.0f;

	buff[1].color = color;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * 2;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	ID3D11Device *dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();
	ID3D11DeviceContext *devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	ID3D11Buffer* pVBuffer;
	dev->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, buff, sizeof(Vertex) * 2);
	devcon->Unmap(pVBuffer, NULL);

	shader->Activate();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	devcon->Draw(2, 0);
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