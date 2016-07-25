#include <Windows.h>
#include "EngineCore.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "GraphicsAPI.h"
#include "SpaceShooterGame.h"
#include "Globals.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	AllocConsole();
	FILE* conout;
	FILE* conin;

	freopen_s(&conout, "CONOUT$", "w", stdout);
	freopen_s(&conin, "CONIN$", "r", stdin);

	SetWindowPos(GetConsoleWindow(), 0, resolution_x, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	fprintf(stdout, "Console Allocated\n");
	SpaceShooterGame* game = new SpaceShooterGame();
	EngineCore::Start(GraphicsAPI_Type::D3D11, resolution_x, resolution_y, game);

	FreeConsole();
	
	return 0;
}