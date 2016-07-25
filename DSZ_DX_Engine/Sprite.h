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

	static Texture* defaultTexture;
	static Sprite* defaultSprite;

public:
	Sprite(Texture* texture = nullptr);
	~Sprite();

	void Render(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 rotation, DirectX::XMFLOAT2 scale);

private:
	static ID3D11Buffer* quadBuff;
	static ID3D11Buffer* indicesBuff;
private:
	Texture* texture;
};