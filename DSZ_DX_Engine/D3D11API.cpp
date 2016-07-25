#include "D3D11API.h"
#include "EngineCore.h"
#include <dxgi.h>

void D3D11API::Create(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;
	scd.BufferDesc.Width = EngineCore::GetRes_x();
	scd.BufferDesc.Height = EngineCore::GetRes_y();

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon
	);

	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)EngineCore::GetRes_x();
	viewport.Height = (float)EngineCore::GetRes_y();
	devcon->RSSetViewports(1, &viewport);

	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	dev->CreateBlendState(&bd, &blendState);

	float bf[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	devcon->OMSetBlendState(blendState, bf, 0xffffffff);
}

void D3D11API::Destroy()
{
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

void D3D11API::BeginScene()
{
	float color[4] = { 100.0f / 255, 149.0f / 255, 237.0f / 255, 1.0f };
	devcon->ClearRenderTargetView(backbuffer, color);
}

void D3D11API::EndScene()
{
	swapchain->Present(0, 0);
}

void* D3D11API::GetDevice()
{
	return (void*)dev;
}

void* D3D11API::GetDeviceContext()
{
	return (void*)devcon;
}

void D3D11API::SetFullScreen(bool bFullscreen)
{
	swapchain->SetFullscreenState(bFullscreen, NULL);
}