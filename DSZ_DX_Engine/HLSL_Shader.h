#pragma once

#include "Shader.h"

#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")

struct ID3D11VertexShader;
struct ID3D11PixelShader;

class HLSL_Shader : public Shader
{
public:
	HLSL_Shader();
	~HLSL_Shader();

	virtual void Compile(const char* vs_filename, const char* ps_fileName) override;
	void Init() override;
	virtual void Activate() override;
	virtual void Clean() override;
	virtual void SetParameters() override;

	
	void SetViewMatrix(DirectX::XMMATRIX viewMatrix);
	void SetWorldMatrix(DirectX::XMMATRIX worldMatrix);

	const ID3D11VertexShader* GetVS() const;
	const ID3D11PixelShader* GetPS() const;
	ID3D10Blob* GetVSBlob() const;
	ID3D10Blob* GetPSBlob() const;

protected:
	virtual void CreateBuffers();
	virtual void DestroyBuffers();
	virtual void SetInputLayout();

protected:
	ID3D11VertexShader *pVS;    // the vertex shader
	ID3D11PixelShader *pPS;     // the pixel shader
	ID3D10Blob *vsBlob, *psBlob;

	ID3D11InputLayout* pLayout;

	ID3D11Buffer* perFrameBuffer;
	ID3D11Buffer* perObjectBuffer;
};