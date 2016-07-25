#pragma once

#include "Component.h"
#include <DirectXMath.h>

class SceneComponent : public Component
{
public:
	DirectX::XMFLOAT2 position	= DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 rotation	= DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 scale		= DirectX::XMFLOAT2(1.0f, 1.0f);
};