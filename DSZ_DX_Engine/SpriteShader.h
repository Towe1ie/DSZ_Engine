#pragma once

#include "HLSL_Shader.h"
#include <DirectXMath.h>

class Texture;

class SpriteShader : public HLSL_Shader
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};

	struct VS_Buffer0
	{
		DirectX::XMMATRIX viewMatrix;
	};

	struct VS_Buffer1
	{
		DirectX::XMMATRIX worldMatrix;
	};

	Texture* texture;

	VS_Buffer0 cpu_vs_buffer0;
	VS_Buffer1 cpu_vs_buffer1;

	virtual void SetParameters() override;
	virtual void SetInputLayout() override;

protected:
	virtual void CreateBuffers() override;
	virtual void DestroyBuffers() override;
protected:
	ID3D11SamplerState* samplerState;

	ID3D11Buffer* gpu_vs_buffer0;
	ID3D11Buffer* gpu_vs_buffer1;
};
