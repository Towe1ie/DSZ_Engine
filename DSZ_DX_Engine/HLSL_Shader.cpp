#include "HLSL_Shader.h"
#include "EngineCore.h"
#include "GraphicsAPI.h"
#include <memory>
#include <iostream>

#include <d3d11.h>
#include <d3dcompiler.h>

using namespace DirectX;

HLSL_Shader::HLSL_Shader()
{

}

HLSL_Shader::~HLSL_Shader()
{
	perFrameBuffer->Release();
	perObjectBuffer->Release();
}

void HLSL_Shader::Compile(const char* vs_filename, const char* ps_filename)
{
	ID3D10Blob* vs;
	ID3D10Blob* ps;
	
	size_t vs_filename_size = strlen(vs_filename) + 1;
	size_t ps_filename_size = strlen(ps_filename) + 1;
	wchar_t* w_vs_filename = new wchar_t[vs_filename_size];
	wchar_t* w_ps_filename = new wchar_t[ps_filename_size];

	size_t ret;
	mbstowcs_s(&ret, w_vs_filename, vs_filename_size, vs_filename, vs_filename_size - 1);
	mbstowcs_s(&ret, w_ps_filename, ps_filename_size, ps_filename, ps_filename_size - 1);

	HRESULT res;

	res = D3DCompileFromFile(
		w_vs_filename,
		0,
		0,
		"main",
		"vs_5_0",
		0,
		0,
		&vs,
		0);

	if (FAILED(res))
	{
		std::cout << "VS Compile fail";
	}

	res = D3DCompileFromFile(
		w_ps_filename,
		0,
		0,
		"main",
		"ps_5_0",
		0,
		0,
		&ps,
		0);

	if (FAILED(res))
	{
		std::cout << "PS Compile fail";
	}

	delete[] w_vs_filename;
	delete[] w_ps_filename;

	ID3D11Device* dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();
	dev->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), NULL, &pVS);
	dev->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &pPS);

	vsBlob = vs;
	psBlob = ps;
}

void HLSL_Shader::Activate()
{
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();
	devcon->IASetInputLayout(pLayout);
	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);
}

void HLSL_Shader::Clean()
{
	pVS->Release();
	pPS->Release();
	DestroyBuffers();
}

const ID3D11VertexShader* HLSL_Shader::GetVS() const
{
	return pVS;
}

const ID3D11PixelShader* HLSL_Shader::GetPS() const
{
	return pPS;
}

ID3D10Blob* HLSL_Shader::GetVSBlob() const
{
	return vsBlob;
}

ID3D10Blob* HLSL_Shader::GetPSBlob() const
{
	return psBlob;
}

void HLSL_Shader::SetInputLayout()
{
	ID3D11Device *dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	
	dev->CreateInputLayout(
		ied,
		2,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&pLayout
	);
}

void HLSL_Shader::SetViewMatrix(DirectX::XMMATRIX viewMatrix)
{
	D3D11_MAPPED_SUBRESOURCE ms;
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	devcon->Map(
		perFrameBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms
	);

	//*((XMMATRIX*)ms.pData) = viewMatrix;
	memcpy(ms.pData, &viewMatrix, sizeof(viewMatrix));

	devcon->Unmap(perFrameBuffer, 0);

	devcon->VSSetConstantBuffers(0, 1, &perFrameBuffer);
}

void HLSL_Shader::SetWorldMatrix(DirectX::XMMATRIX worldMatrix)
{
	D3D11_MAPPED_SUBRESOURCE ms;
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	devcon->Map(
		perObjectBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms
	);

	//*((XMMATRIX*)ms.pData) = viewMatrix;
	memcpy(ms.pData, &worldMatrix, sizeof(worldMatrix));

	devcon->Unmap(perObjectBuffer, 0);

	devcon->VSSetConstantBuffers(1, 1, &perObjectBuffer);
}

void HLSL_Shader::Init()
{
	CreateBuffers();
	SetInputLayout();
}

void HLSL_Shader::CreateBuffers()
{
	D3D11_BUFFER_DESC mbd;

	mbd.Usage = D3D11_USAGE_DYNAMIC;
	mbd.ByteWidth = sizeof(XMMATRIX);
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.MiscFlags = 0;
	mbd.StructureByteStride = 0;

	ID3D11Device* dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();

	dev->CreateBuffer(
		&mbd,
		NULL,
		&perFrameBuffer
	);

	dev->CreateBuffer(
		&mbd,
		NULL,
		&perObjectBuffer
	);
}

void HLSL_Shader::DestroyBuffers()
{
	perFrameBuffer->Release();
	perObjectBuffer->Release();
}


void HLSL_Shader::SetParameters()
{

}