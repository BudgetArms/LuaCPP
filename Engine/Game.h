//-----------------------------------------------------------------
// Main Game  File
// C++ Header - Game.h - version v8_01			
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"


// include sol
#include <sol/sol.hpp>


//-----------------------------------------------------------------
// Game Class																
//-----------------------------------------------------------------
class Game : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Game();

	virtual ~Game() override;


	void BindAllTypes(); // custom function

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	Game(const Game& other)					= delete;
	Game(Game&& other) noexcept				= delete;
	Game& operator=(const Game& other)		= delete;
	Game& operator=(Game&& other) noexcept	= delete;

	//---------------------------
	// General Member Functions
	//---------------------------
	void Initialize			()															override;
	void Start				()															override;
	void End				()															override;
	void Paint				(RECT rect)	const											override;
	void Tick				()															override;
	void MouseButtonAction	(bool isLeft, bool isDown, int x, int y, WPARAM wParam)		override;
	void MouseWheelAction	(int x, int y, int distance, WPARAM wParam)					override;
	void MouseMove			(int x, int y, WPARAM wParam)								override;
	void CheckKeyboard		()															override;
	void KeyPressed			(TCHAR key)													override;
	
	void CallAction			(Caller* callerPtr)											override;

private:
	// -------------------------
	// Datamembers
	// -------------------------

	sol::state m_Lua;

	sol::function m_FnBeginGame;
	sol::function m_FnDestroyGame;
	sol::function m_FnInitialize;
	sol::function m_FnStart;
	sol::function m_FnEnd;
	sol::function m_FnPaint;
	sol::function m_FnTick;
	sol::function m_FnMouseButtonAction;
	sol::function m_FnMouseWheelAction;
	sol::function m_FnMouseMove;
	sol::function m_FnCheckKeyboard;
	sol::function m_FnKeyPressed;
	sol::function m_FnCallAction;


};
