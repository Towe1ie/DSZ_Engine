#include "EngineCore.h"
#include "Input.h"
#include <stdio.h>
#include "GraphicsAPI.h"
#include "D3D11API.h"
#include "BasicGeomentry.h"
#include "HLSL_Shader.h"
#include "Grid.h"
#include "Camera.h"
#include "Globals.h"
#include "Game.h"
#include "Sprite.h"
#include "SpriteShader.h"
#include "Renderer.h"
#include "World.h"
#include "BasicShader.h"
#include "PhysicsManager.h"
#include "Level.h"
#include "Task.h"
#include "AIController.h"

EngineCore* EngineCore::engineInstance = nullptr;
LPCWSTR EngineCore::engineName = L"DSZ_DX_Engine";

EngineCore::EngineCore(UINT res_x, UINT res_y, Game* game)
	: hwnd(NULL), hinstance(NULL), res_x(res_x), res_y(res_y), currentGame(game)
{
	Initialize();
}

EngineCore::~EngineCore()
{
	delete currentAPI;
}

EngineCore* EngineCore::GetInstance()
{
	return engineInstance;
}

GraphicsAPI* EngineCore::GetGraphicsAPI()
{
	if (engineInstance)
		return engineInstance->currentAPI;

	return nullptr;
}

void EngineCore::Start(GraphicsAPI_Type api, UINT res_x, UINT res_y, Game* game)
{
	if (!engineInstance)
	{
		engineInstance = new EngineCore(res_x, res_y, game);
	}

	Input::Initialize();

	switch (api)
	{
		case GraphicsAPI_Type::D3D11:
			engineInstance->currentAPI = new D3D11API;
			break;
	}

	engineInstance->currentAPI->Create(engineInstance->hwnd);

	engineInstance->gameLoop();
}

void EngineCore::Shutdown()
{
	engineInstance->destroyWindow();
	engineInstance->currentAPI->Destroy();
	delete engineInstance;
}

void EngineCore::Initialize()
{
	this->hinstance = GetModuleHandle(NULL);

	createWindow();
}

void EngineCore::createWindow()
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = engineName;
	wc.hIconSm = wc.hIcon;

	RegisterClassEx(&wc);

	this->hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		engineName,
		engineName,
		WS_CLIPCHILDREN | WS_CLIPCHILDREN | WS_POPUP,
		0,
		0,
		res_x,
		res_y,
		NULL,
		NULL,
		hinstance,
		NULL);

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	ShowCursor(true);
}

void EngineCore::destroyWindow()
{
	ShowCursor(true);

	DestroyWindow(hwnd);
	hwnd = NULL;

	UnregisterClass(engineName, hinstance);

	hinstance = NULL;
}

void EngineCore::gameLoop()
{
	MSG msg;

	Sprite::SpriteShader = new SpriteShader();
	Sprite::SpriteShader->Compile("SpriteVS.hlsl", "SpritePS.hlsl");
	Sprite::SpriteShader->Init();
	Sprite::Init();


	basicShader = new BasicShader();
	basicShader->Compile("BasicVS.hlsl", "BasicPS.hlsl");
	basicShader->Init();

	Grid grid(20);

	Level* defaultLevel = World::CreateNewLevel();
	World::SetCurrentLevel(defaultLevel);

	Camera camera(res_x / (float)res_y);
	camera.SetWidth(40);
	defaultLevel->AddCamera(&camera);
	defaultLevel->currentCamera = &camera;

	currentGame->LoadContent();

	while (1)
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		
		this->gameTime.currentTime = currentTime;

		double elapsed = gameTime.dt();

		if (elapsed >= 1 / targetFPS)
		{
			Input::Update();

			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			Task::Update(gameTime);
			World::Update(gameTime);
			AIController::UpdateAllControllers(gameTime);
			PhysicsManager::Update(gameTime);
			currentGame->Update(gameTime);

			if (Input::IsKeyDown(Key::ESC))
				break;

			currentAPI->BeginScene();
			grid.Render();
			Renderer::Render();
			currentGame->Render();
			currentAPI->EndScene();

			Input::scrollValue = 0.f;

			this->gameTime.lastUpdateTime = this->gameTime.currentTime;
		}
	}

	currentGame->UnloadContent();
	Sprite::Uninit();
}

UINT EngineCore::GetRes_x()
{
	return engineInstance->res_x;
}

UINT EngineCore::GetRes_y()
{
	return engineInstance->res_y;
}

LRESULT CALLBACK EngineCore::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			Input::KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			Input::KeyUp((unsigned int)wparam);
			return 0;
		}

		case WM_LBUTTONDOWN:
		{
			Input::ButtonDown(LEFT);
			return 0;
		}

		case WM_MBUTTONDOWN:
		{
			Input::ButtonDown(MIDDLE);
			return 0;
		}

		case WM_RBUTTONDOWN:
		{
			Input::ButtonDown(RIGHT);
			return 0;
		}

		case WM_LBUTTONUP:
		{
			Input::ButtonUp(LEFT);
			return 0;
		}

		case WM_MBUTTONUP:
		{
			Input::ButtonUp(MIDDLE);
			return 0;
		}

		case WM_RBUTTONUP:
		{
			Input::ButtonUp(RIGHT);
			return 0;
		}

		case WM_MOUSEWHEEL:
		{
			Input::scrollValue = (float)(GET_WHEEL_DELTA_WPARAM(wparam));
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uMsg)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return EngineCore::GetInstance()->MessageHandler(hwnd, uMsg, wParam, lParam);
		}
	}
}

