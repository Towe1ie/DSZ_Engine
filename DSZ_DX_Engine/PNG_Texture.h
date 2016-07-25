#pragma once

#include "Texture.h"
#include <d3d11.h>

class PNG_Texture : public Texture
{
public:
	~PNG_Texture() override;
	void Load(const char* fileName) override;

	ID3D11Texture2D* GetTexture2D();
	ID3D11ShaderResourceView* GetShaderResourceView();

private:
	unsigned int width, height;
	unsigned char* image_data;
	int color_type, bit_depth;

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureView;
};