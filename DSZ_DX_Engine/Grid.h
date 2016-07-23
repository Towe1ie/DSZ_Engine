#pragma once

#include <d3d11.h>

class Grid
{
public:
	Grid(UINT n = 10);
	~Grid();

	void Render();
private:
	ID3D11Buffer* buff;

	UINT n;
};