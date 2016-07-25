#include "BasicShader.h"
#include "EngineCore.h"

using namespace DirectX;

void BasicShader::CreateBuffers()
{
	D3D11_BUFFER_DESC mbd;

	mbd.Usage = D3D11_USAGE_DYNAMIC;
	mbd.ByteWidth = sizeof(VS_Buffer0);
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.MiscFlags = 0;
	mbd.StructureByteStride = 0;

	ID3D11Device* dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();

	dev->CreateBuffer(
		&mbd,
		NULL,
		&gpu_vs_buffer0
	);
}

void BasicShader::DestroyBuffers()
{
	gpu_vs_buffer0->Release();
}


void BasicShader::SetParameters()
{
	D3D11_MAPPED_SUBRESOURCE ms0;
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();
	
	// Set buffer 0
	devcon->Map(
		gpu_vs_buffer0,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms0
	);

	memcpy(ms0.pData, &cpu_vs_buffer0, sizeof(cpu_vs_buffer0));
	devcon->Unmap(gpu_vs_buffer0, 0);
	devcon->VSSetConstantBuffers(0, 1, &gpu_vs_buffer0);
}

void BasicShader::SetInputLayout()
{
	ID3D11Device *dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	dev->CreateInputLayout(
		ied,
		1,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&pLayout
	);
}