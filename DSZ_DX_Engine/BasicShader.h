#pragma once

#include "HLSL_Shader.h"
#include <DirectXMath.h>

class BasicShader : public HLSL_Shader
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
		DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	};

	struct VS_Buffer0
	{
		DirectX::XMMATRIX viewMatrix;
		DirectX::XMMATRIX worldMatrix;
		DirectX::XMFLOAT4 color;
		bool useVertexColor;
	};

	VS_Buffer0 cpu_vs_buffer0;

	virtual void SetParameters() override;
	virtual void SetInputLayout() override;

protected:
	virtual void CreateBuffers() override;
	virtual void DestroyBuffers() override;

	ID3D11Buffer* gpu_vs_buffer0;
};