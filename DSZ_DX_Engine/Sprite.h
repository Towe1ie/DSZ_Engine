#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

class Texture;
class SpriteShader;


class Sprite
{
public:
	static SpriteShader* SpriteShader;
	static void Init();
	static void Uninit();

	DirectX::XMFLOAT3 pos;
public:
	Sprite(Texture* texture);
	~Sprite();

	void Render();

private:
	static ID3D11Buffer* quadBuff;
	static ID3D11Buffer* indicesBuff;
private:
	Texture* texture;
};