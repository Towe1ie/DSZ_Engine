#include "Sprite.h"
#include "SpriteShader.h"
#include "EngineCore.h"
#include "Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

SpriteShader* Sprite::SpriteShader = nullptr;
ID3D11Buffer* Sprite::quadBuff = nullptr;
ID3D11Buffer* Sprite::indicesBuff = nullptr;

Sprite::Sprite(Texture* texture)
	: texture(texture)
{
}

Sprite::~Sprite()
{

}

void Sprite::Render()
{
	Sprite::SpriteShader->Activate();
	Sprite::SpriteShader->cpu_vs_buffer0.viewMatrix = EngineCore::GetCurrentCamera()->GetViewMatrix();
	Sprite::SpriteShader->cpu_vs_buffer1.worldMatrix = XMMatrixTranspose(XMMatrixTranslation(pos.x, pos.y, 0.f));
	Sprite::SpriteShader->texture = texture;
	Sprite::SpriteShader->SetParameters();

	unsigned int stride = sizeof(SpriteShader::Vertex);
	unsigned int offset = 0;

	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();
	devcon->IASetVertexBuffers(0, 1, &quadBuff, &stride, &offset);
	devcon->IASetIndexBuffer(indicesBuff, DXGI_FORMAT_R32_UINT, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcon->DrawIndexed(6, 0, 0);
}

void Sprite::Init()
{
	SpriteShader::Vertex vertices[4];
	unsigned long indices[6];
	D3D11_BUFFER_DESC vdesc, idesc;
	D3D11_SUBRESOURCE_DATA vdata, idata;
	ID3D11Device* dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	// Vertex buffer
	vertices[0].pos = XMFLOAT3(1.f, -1.f, 0.f);
	vertices[1].pos = XMFLOAT3(-1.f, -1.f, 0.f);
	vertices[2].pos = XMFLOAT3(-1.f, 1.f, 0.f);
	vertices[3].pos = XMFLOAT3(1.f, 1.f, 0.f);

	vertices[3].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[2].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[1].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[0].uv = XMFLOAT2(1.0f, 0.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	vdesc.Usage = D3D11_USAGE_DEFAULT;
	vdesc.ByteWidth = sizeof(SpriteShader::Vertex) * 4;
	vdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vdesc.CPUAccessFlags = 0;
	vdesc.MiscFlags = 0;
	vdesc.StructureByteStride = 0;

	vdata.pSysMem = vertices;
	vdata.SysMemPitch = 0;
	vdata.SysMemSlicePitch = 0;

	dev->CreateBuffer(&vdesc, &vdata, &quadBuff);

	// Index buffer
	idesc.Usage = D3D11_USAGE_DEFAULT;
	idesc.ByteWidth = sizeof(unsigned long) * 6;
	idesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	idesc.CPUAccessFlags = 0;
	idesc.MiscFlags = 0;
	idesc.StructureByteStride = 0;

	idata.pSysMem = indices;
	idata.SysMemPitch = 0;
	idata.SysMemSlicePitch = 0;

	dev->CreateBuffer(&idesc, &idata, &indicesBuff);
}

void Sprite::Uninit()
{
	quadBuff->Release();
	indicesBuff->Release();
}