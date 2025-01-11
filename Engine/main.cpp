#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>

//#include "Flower.h"
#include "GameEngine.h"
#include "Game.h"

extern GameEngine* GAME_ENGINE;

void RunGame();
void SetGamer();


int main()
{
	try
	{

		std::cout << "main\n";

		sol::state lua;

		lua.open_libraries(sol::lib::base);




		lua["Game"] = GAME_ENGINE;


		lua.new_usertype<GameEngine>
			(
				"GameEngine", sol::constructors<GameEngine()>(),
				"RunGame", RunGame,
				"GAMERS", SetGamer,

				"SetTitle", &GameEngine::SetTitle,
				"SetWindowPosition", &GameEngine::SetWindowPosition,
				"SetKeyList", &GameEngine::SetKeyList,
				"SetFrameRate", &GameEngine::SetFrameRate,
				"SetWidth", &GameEngine::SetWidth,
				"SetHeight", &GameEngine::SetHeight,
				"GoFullScreen", &GameEngine::GoFullscreen,
				"GoWindowedMode", &GameEngine::GoWindowedMode,
				"SetMouseVisibility", &GameEngine::ShowMousePointer,
				"Quit", &GameEngine::Quit,
				"HasWindowRegion", &GameEngine::HasWindowRegion,
				"IsFullscreen", &GameEngine::IsFullscreen,

				//"CreateWindow", &GameEngine::

				"IsKeyDown", &GameEngine::IsKeyDown,
				//"MessageBox", &GameEngine::MessageBox,
				//"MessageBox", sol::overload(
					//sol::resolve<void(const tstring&) const> (&GameEngine::MessageBox),
					//sol::resolve<void(const TCHAR*) const> (&GameEngine::MessageBox)
				//),
				"SetColor", &GameEngine::SetColor,
				"DrawLine", &GameEngine::DrawLine,
				"DrawRect", &GameEngine::DrawRect,
				"FillRect", sol::overload(
					sol::resolve<bool(int, int, int, int) const>(&GameEngine::FillRect),
					sol::resolve<bool(int, int, int, int, int) const>(&GameEngine::FillRect)
				),
				"DrawRoundRect", &GameEngine::DrawRoundRect,
				"FillRoundRect", &GameEngine::FillRoundRect,
				"DrawOval", &GameEngine::DrawOval,
				"FillOval", sol::overload(
					sol::resolve<bool(int, int, int, int) const>(&GameEngine::FillOval),
					sol::resolve<bool(int, int, int, int, int) const>(&GameEngine::FillOval)),
				"DrawArc", &GameEngine::DrawArc,
				"FillArc", &GameEngine::FillArc,
				"DrawString", sol::overload(
					sol::resolve<int(const tstring&, int, int) const>(&GameEngine::DrawString),
					sol::resolve<int(const tstring&, int, int, int, int) const>(&GameEngine::DrawString)
				),
				"Repaint", &GameEngine::Repaint,
				"GetTitle", &GameEngine::GetTitle,
				"GetWidth", &GameEngine::GetWidth,
				"GetHeight", &GameEngine::GetHeight,
				"GetFrameRate", &GameEngine::GetFrameRate,
				"GetFrameDelay", &GameEngine::GetFrameDelay
			);





		// Bind HINSTANCE (just a void pointer in Lua, no need to use `new` types)
		//lua.new_usertype<HINSTANCE>("HINSTANCE");

		// Bind WPARAM (just a uintptr_t in Lua)
		lua.new_usertype<WPARAM>("WPARAM");

		// Bind the Caller function pointer type
		//lua.set_function("sampleCaller", sampleCaller);




		const auto scriptResult = lua.script_file("GameEngine.lua");
		if (!scriptResult.valid())
		{
			// Handle Script error
			const sol::error err = scriptResult;
			std::cerr << "Load Script Error: " << err.what() << "\n";
			return -1;
		}

		//RunGame();

	}
	catch (const std::exception& e)
	{
		std::cerr << "Current Directory: " << std::filesystem::current_path() << "\n";
		std::cerr << "Error catched: " << e.what() << "\n";
	}
	

	std::cout << "END THINGY" << "\n";


	return 0;
}



void RunGame()
{
	std::cout << "RunGame" << "\n";
	std::cout << GAME_ENGINE << "\n";
	
	// Simulate initializing from GameWinMain to set `hInstance` and `nCmdShow`
	HINSTANCE hInstance = GetModuleHandle(nullptr);  // Typically retrieved in wWinMain
	int nCmdShow = SW_SHOWNORMAL;  // Typical default for nCmdShow, but can be customized.

	//GAME_ENGINE->SetGame(new Game());
	//GAME_ENGINE->Run(hInstance, nCmdShow);



} 



void SetGamer()
{
	GAME_ENGINE->SetGame(new Game());

}
