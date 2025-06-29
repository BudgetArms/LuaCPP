---@meta
--- This file provides type annotations for Lua scripts interacting with C++ via SOL2.
--- Game Specific

function Game:Initialize() end

function Game:Start() end
function Game:End() end
function Game:MouseButtonAction(isLeft, isDown, x, y, wParam) end
function Game:MouseWheelAction(x, y, distance, wParam) end
function Game:MouseMove(x, y, wParam) end
function Game:CheckKeyboard() end
function Game:KeyPressed(key) end
function Game:Paint(rect) end
function Game:Tick() end

function Game:CallAction(callerPtr) end


