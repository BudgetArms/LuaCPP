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
    // nothing to create
    try
    {

        m_Lua.open_libraries(sol::lib::base, sol::lib::math); //sol::lib::math, sol::lib::string, ...

        BindAllTypes();

        m_Lua["GameEngine"] = GAME_ENGINE;


        const std::string gamePath{ "Game/Game.lua" };

        if (!std::filesystem::exists(gamePath))
            throw std::exception("ERROR: LUA FILE NOT FOUND");

        m_Lua.safe_script_file(gamePath);

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


    }
    catch (const std::exception& e)
    {
        std::cout << "Win Exception: " << e.what();
        throw("SHIT IS F?CKED");
    }

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



    m_Lua.new_usertype<RECT>
        (
            "RECT",
            "left", &RECT::left,
            "top", &RECT::top,
            "right", &RECT::right,
            "bottom", &RECT::bottom
        );

}


void Game::Initialize()
{
    // Code that needs to execute (once) at the start of the game, before the game window is created

    AbstractGame::Initialize();
    GAME_ENGINE->SetTitle(_T("Game Engine version 8_01"));

    GAME_ENGINE->SetWidth(1024);
    GAME_ENGINE->SetHeight(768);
    GAME_ENGINE->SetFrameRate(50);

    m_FnInitialize();
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
    m_FnPaint(rect);
}

void Game::Tick()
{
    // Insert non-paint code that needs to execute each tick 
    m_FnTick();

}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
    // Insert code for a mouse button action
    m_FnMouseButtonAction(isLeft, isDown, x, y, wParam);
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{
    // Insert code for a mouse wheel action
    m_FnMouseWheelAction(x, y, distance, wParam);
}

void Game::MouseMove(int x, int y, WPARAM wParam)
{
    // Insert code that needs to execute when the mouse pointer moves across the game window
    m_FnMouseMove(x, y, wParam);
}

void Game::CheckKeyboard()
{
    // Here you can check if a key is pressed down
    // Is executed once per frame 
    m_FnCheckKeyboard();

    /* Example:
    if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
    if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
    if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
    if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
    */
}

void Game::KeyPressed(TCHAR key)
{
    // Insert code that needs to execute when a key is pressed
    // The function is executed when the key is *released*
    // You need to specify the list of keys with the SetKeyList() function
    m_FnKeyPressed(key);
}

void Game::CallAction(Caller* callerPtr)
{
    // Insert the code that needs to execute when a Caller (= Button, TextBox, Timer, Audio) executes an action
    m_FnCallAction(callerPtr);
}


