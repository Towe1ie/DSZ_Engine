#include "SpriteShader.h"
#include "EngineCore.h"
#include "Camera.h"
#include "PNG_Texture.h"

using namespace DirectX;


void SpriteShader::SetParameters()
{
	D3D11_MAPPED_SUBRESOURCE ms0, ms1;
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

	// Set buffer 1
	devcon->Map(
		gpu_vs_buffer1,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms1
	);

	memcpy(ms1.pData, &cpu_vs_buffer1, sizeof(cpu_vs_buffer1));
	devcon->Unmap(gpu_vs_buffer1, 0);
	devcon->VSSetConstantBuffers(1, 1, &gpu_vs_buffer1);

	PNG_Texture* png_tex = (PNG_Texture*)texture;
	ID3D11ShaderResourceView* srv = png_tex->GetShaderResourceView();
	devcon->PSSetShaderResources(0, 1, &srv);

	devcon->PSSetSamplers(0, 1, &samplerState);
}

void SpriteShader::SetInputLayout()
{
	ID3D11Device *dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	dev->CreateInputLayout(
		ied,
		2,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&pLayout
	);
}

void SpriteShader::CreateBuffers()
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
		&gpu_vs_buffer0
	);

	dev->CreateBuffer(
		&mbd,
		NULL,
		&gpu_vs_buffer1
	);

	D3D11_SAMPLER_DESC sd;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MipLODBias = 0.0f;
	sd.MaxAnisotropy = 1;
	sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sd.BorderColor[0] = 0;
	sd.BorderColor[1] = 0;
	sd.BorderColor[2] = 0;
	sd.BorderColor[3] = 0;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	dev->CreateSamplerState(
		&sd,
		&samplerState
	);
}

void SpriteShader::DestroyBuffers()
{
	gpu_vs_buffer0->Release();
	gpu_vs_buffer1->Release();
	samplerState->Release();
}
