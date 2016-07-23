#pragma once

#include "GraphicsAPI.h"

#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


class D3D11API : public GraphicsAPI
{
public:
	void Create(HWND hwnd) override;
	void Destroy() override;
	//void Render() override;
	void* GetDevice() override;
	void* GetDeviceContext() override;

	void BeginScene() override;
	void EndScene() override;
private:
	// global declarations
	IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
	ID3D11Device *dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer;    // global declaration
	ID3D11BlendState *blendState;
};