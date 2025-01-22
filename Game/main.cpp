#include <sol/sol.hpp>
#include <iostream>
#include <filesystem>

#include "../Engine/GameEngine.h"
#include "../Engine/Game.h"

extern GameEngine* GAME_ENGINE;


// This file is currently used for testing how Lua/SOL2 work
int main()
{
	try
	{

		std::cout << "main.cpp\n";

		sol::state lua;

		// calls standard libs
		lua.open_libraries();

		lua["Game"] = GAME_ENGINE;


		lua.new_usertype<GameEngine>
			(
				//"GameEngine", sol::no_constructor,
				"GameEngine", sol::constructors<GameEngine()>(),
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
				"IsKeyDown", &GameEngine::IsKeyDown,

				//"MessageBox", sol::overload(
				//	sol::resolve<void(const tstring&) const> (&GameEngine::MessageBox),
				//	sol::resolve<void(const TCHAR*) const> (&GameEngine::MessageBox)
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


		//lua.new_usertype<HINSTANCE>("HINSTANCE");

		lua.new_usertype<WPARAM>("WPARAM");

		//lua.set_function("sampleCaller", sampleCaller);


		const auto scriptResult = lua.script_file("Game/GameEngine.lua");
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
