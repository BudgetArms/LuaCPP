--- script_annotations.lua has the annotations EmmyLua annotations for the GameEngine

print("GameEngine.lua")
print("Cool :D")

--print("Game", Game)

--Game:SetTitle("COOL")


--print("Game Title:", Game:GetTitle())


--Game:SetTitle("COOL")

--Game:GoFullScreen(true)


print("END of Lua ???")


function NormalFunction()
    print("Normal Function in Lua")
end

Yeah={}
TestGameEngine ={}

--[[
]]

Game = {}
print("Yeah: ", Yeah)

print("TestGameEngine: ", TestGameEngine)
print("Game: ", Game)
function Game:BeginGame()
    print("Lua: Game Begin")
end

function Game:DestroyGame()
    print("Lua: Game Destroy")
end

function Game:InitializeGame()
    print("Lua: Initializing Game")
end

function Game:GameStart()
    print("Lua: Game Start")
end

function Game:GameEnd()
    print("Lua: Game End")
end

function Game:Paint(rect)
    print("Lua: Paint called for", rect)
end

function Game:Tick()
    print("Lua: Tick called")
end

function Game:MouseButtonAction(button, x, y)
    print("Lua: Mouse button", button, "at", x, y)
end

function Game:MouseWheelAction(delta, x, y)
    print("Lua: Mouse wheel", delta, "at", x, y)
end

function Game:MouseMove(x, y)
    print("Lua: Mouse move at", x, y)
end

function Game:CheckKeyKeyboard()
    print("Lua: Checking Keyboard")
end

function Game:KeyPressed(key)
    print("Lua: Key pressed", key)
end

function Game:CallAction(action)
    print("Lua: Action called", action)
end



--]]


