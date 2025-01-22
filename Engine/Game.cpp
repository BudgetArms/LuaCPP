//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

//-----------------------------------------------------------------
// Game Member Functions																				
//-----------------------------------------------------------------



// Custom Includes
#include <filesystem>




Game::Game()
{



}

Game::~Game()																						
{
	// nothing to destroy
	m_FnDestroyGame();
}

void Game::BindAllTypes()
{
	m_Lua.new_usertype<GameEngine>
		(
			"GameEngine", sol::no_constructor,
			//"GameEngine", sol::constructors<GameEngine()>(),
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
 
	/*m_Lua.new_usertype<Game>
		(
			"Game", sol::no_constructor,
			"PaintGame", &Game::Paint,
			"TickGame", &Game::Tick,
			"MouseButtonActionGame", &Game
		);*/




}


void Game::Initialize()			
{
	// Code that needs to execute (once) at the start of the game, before the game window is created

	AbstractGame::Initialize();
	GAME_ENGINE->SetTitle(_T("Game Engine version 8_01"));	
	
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
    GAME_ENGINE->SetFrameRate(50);



	m_Lua.open_libraries();

	m_Lua["TestGameEngine"] = GAME_ENGINE;
	m_Lua["Yeah"] = GAME_ENGINE;
	m_Lua["Game"] = m_Lua.create_table();

	BindAllTypes();

	m_FnBeginGame = m_Lua["BeginGame"];
	m_FnDestroyGame = m_Lua["DestroyGame"];
	m_FnInitialize = m_Lua["InitializeGame"];
	m_FnStart = m_Lua["GameStart"];
	m_FnEnd = m_Lua["GameEnd"];
	m_FnPaint = m_Lua["Paint"];
	m_FnTick = m_Lua["Tick"];
	m_FnMouseButtonAction = m_Lua["MouseButtonAction"];
	m_FnMouseWheelAction = m_Lua["MouseWheelAction"];
	m_FnMouseMove = m_Lua["MouseMove"];
	m_FnCheckKeyboard = m_Lua["CheckKeyKeyboard"];
	m_FnKeyPressed = m_Lua["KeyPressed"];
	m_FnCallAction = m_Lua["CallAction"];

	//m_FnCheckKeyboard	= m_Lua["Game"]["CheckKeyKeyboard"];

	auto fnTest = m_Lua["NormalFunction"];



	//ValidateFunction(m_Lua, "Game", "BeginGame");

	//sol::protected_function m_FnBeginGame = m_Lua["Game"]["BeginGame"];
	if (m_FnBeginGame.valid())
	{
		sol::protected_function_result result = m_FnBeginGame();
		if (!result.valid())
		{
			sol::error err = result;
			std::cerr << "Error calling BeginGame: " << err.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "BeginGame function is not valid or not found in Lua." << std::endl;
	}



	std::cout << "GAME_ENGINE (CPP): " << GAME_ENGINE << "\n";
	std::cout << "ENGINE: " << this << "\n";

	const std::string gamePath{ "Game/Game.lua" };
	if (!std::filesystem::exists(gamePath))
	{
		std::cout << "ERROR: LUA FILE NOT FOUND" << "\n";
		throw std::exception("THIS SHIT FAILED SOOO HARD");
	}

	// if satety on, script => safe_file else unsafe_file
	const auto scriptResult = m_Lua.safe_script_file(gamePath);
	if (!scriptResult.valid())
	{
		const sol::error err = scriptResult;
		std::cerr << "ERROR: Load Script: " << err.what();

		throw std::exception("THIS SHIT FAILED EVEN HARDER");
	}


	if (m_FnCheckKeyboard.valid())
	{
		std::cout << "VALID BEGIN GAME" << "\n";

	}
	else
	{
		std::cout << "INVALID BEGIN GAME" << "\n";

	}

	fnTest();
	m_Lua["Yeah"] = GAME_ENGINE;





	if (m_FnInitialize.valid())
		m_FnInitialize();
	else
		std::cout << "not valid" << "\n";

	
	// Set the keys that the game needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (char) VK_LEFT;
	//buffer << (char) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void Game::Start()
{
	// Insert code that needs to execute (once) at the start of the game, after the game window is created
	m_FnStart();
}

void Game::End()
{
	// Insert code that needs to execute when the game ends
	m_FnEnd();
}

void Game::Paint(RECT rect) const
{
	// Insert paint code 
	m_FnPaint();
}

void Game::Tick()
{
	// Insert non-paint code that needs to execute each tick 
	
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	m_FnMouseButtonAction(isLeft, isDown, x, y, wParam);

	// Insert code for a mouse button action

	/* Example:
	if (isLeft == true && isDown == true) // is it a left mouse click?
	{
		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
		{
			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
			{
				GAME_ENGINE->MessageBox(_T("Clicked."));
			}
		}
	}
	*/
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	m_FnMouseWheelAction(x, y, distance, wParam);

	// Insert code for a mouse wheel action
}

void Game::MouseMove(int x, int y, WPARAM wParam)
{	
	m_FnMouseMove(x, y, wParam);


	// Insert code that needs to execute when the mouse pointer moves across the game window

	/* Example:
	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
	{
		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
		{
			GAME_ENGINE->MessageBox("Mouse move.");
		}
	}
	*/
}

void Game::CheckKeyboard()
{	
	m_FnCheckKeyboard();
	// Here you can check if a key is pressed down
	// Is executed once per frame 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/
}

void Game::KeyPressed(TCHAR key)
{	
	m_FnKeyPressed(key);
	// DO NOT FORGET to use SetKeyList() !!

	// Insert code that needs to execute when a key is pressed
	// The function is executed when the key is *released*
	// You need to specify the list of keys with the SetKeyList() function

	/* Example:
	switch (key)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox("Moving left.");
		break;
	case _T('L'): case VK_DOWN:
		GAME_ENGINE->MessageBox("Moving down.");
		break;
	case _T('M'): case VK_RIGHT:
		GAME_ENGINE->MessageBox("Moving right.");
		break;
	case _T('O'): case VK_UP:
		GAME_ENGINE->MessageBox("Moving up.");
		break;
	case VK_ESCAPE:
		GAME_ENGINE->MessageBox("Escape menu.");
	}
	*/
}

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to execute when a Caller (= Button, TextBox, Timer, Audio) executes an action
}




