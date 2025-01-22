//-----------------------------------------------------------------
// Game Engine WinMain Function
// C++ Source - GameWinMain.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameWinMain.h"
#include "GameEngine.h"

#include "Game.h"	

//-----------------------------------------------------------------
// Create GAME_ENGINE global (singleton) object and pointer
//-----------------------------------------------------------------
GameEngine myGameEngine;
GameEngine* GAME_ENGINE{ &myGameEngine };

//-----------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

#if defined(DEBUG) || defined(_DEBUG)
	// Creates console window
	AllocConsole();
	// Redirect stdout to the console, so we can debug
	freopen("CONOUT$", "w", stdout); 
#endif


	GAME_ENGINE->SetGame(new Game());					// any class that implements AbstractGame
	std::cout << "wWinMain start" << "\n";
	return GAME_ENGINE->Run(hInstance, nCmdShow);		// here we go

}



