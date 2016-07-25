#pragma once

#include <Windows.h>
#include "GraphicsAPI.h"
#include "GameTime.h"

class Game;
class Camera;


class EngineCore
{
public:

	static void Start(GraphicsAPI_Type api, UINT res_x, UINT res_y, Game* game);
	static void Shutdown();

	static EngineCore* GetInstance();
	static GraphicsAPI* GetGraphicsAPI();

	//static Camera* GetCurrentCamera();

	static UINT GetRes_x();
	static UINT GetRes_y();
private:
	EngineCore(UINT res_x, UINT res_y, Game* game);
	EngineCore(const EngineCore&);
	~EngineCore();

	void Initialize();

	void createWindow();
	void destroyWindow();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	void gameLoop();

private:
	static EngineCore *engineInstance;
	static LPCWSTR engineName;

	HWND hwnd;
	HINSTANCE hinstance;

	GraphicsAPI* currentAPI;

	//Camera* currentCamera;
	UINT res_x, res_y;

	GameTime gameTime;

	Game* currentGame;

	friend LRESULT CALLBACK WindowProc(
		_In_ HWND   hwnd,
		_In_ UINT   uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	);
	
};

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);