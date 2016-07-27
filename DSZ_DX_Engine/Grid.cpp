#include "Grid.h"
#include "EngineCore.h"
#include "BasicGeomentry.h"
#include "HLSL_Shader.h"
#include <vector>
#include "Globals.h"
#include "BasicShader.h"
#include "World.h"
#include "Level.h"
#include "Camera.h"

using namespace std;

Grid::Grid(UINT n)
	: n(n)
{
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();
	ID3D11Device* dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();
	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	UINT cntV = 2 * (2 * n + 1);
	UINT size = cntV * sizeof(Vertex);

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = size;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	dev->CreateBuffer(
		&bd,
		NULL,
		&buff
	);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(
		buff,
		NULL,
		D3D11_MAP_WRITE_DISCARD,
		NULL,
		&ms
	);

	vector<Vertex> cpu_buff;
	float currX = -(float)n;
	for (UINT i = 0; i < cntV / 2; ++i)
	{
		cpu_buff.push_back(Vertex(XMFLOAT3(currX, (float)n, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)));
		cpu_buff.push_back(Vertex(XMFLOAT3(currX, -(float)n, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)));
		currX += 1.0f;
	}

	
	cpu_buff[cntV / 2 - (cntV / 2) % 2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	cpu_buff[cntV / 2 + !((cntV / 2) % 2)].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	memcpy(ms.pData, cpu_buff.data(), size);

	devcon->Unmap(buff, 0);
}

Grid::~Grid()
{
	buff->Release();
}

void Grid::Render()
{
	basicShader->cpu_vs_buffer0.viewMatrix = World::GetCurrentLevel()->currentCamera->GetViewMatrix();
	basicShader->cpu_vs_buffer0.worldMatrix = XMMatrixIdentity();
	basicShader->cpu_vs_buffer0.useVertexColor = true;
	basicShader->SetParameters();
	basicShader->Activate();
	

	ID3D11DeviceContext *devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &buff, &stride, &offset);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	devcon->Draw(2*(n * 2 + 1), 0);

	basicShader->cpu_vs_buffer0.worldMatrix = XMMatrixRotationZ(XM_PIDIV2);
	basicShader->SetParameters();
	devcon->Draw(2 * (n * 2 + 1), 0);
}