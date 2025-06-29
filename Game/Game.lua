print("GameEngine.lua")
print("Very Cool :D")

local hasWon = false
local hasLost = false

local grayColor = 0x00F0F0F0

local paddleX = 0
local paddleY = 0
local paddleWidth = 175
local paddleHeight = 20
local paddleSpeed = 8

local ballX = 0
local ballY = 0
local ballRadius = 15
local ballSpeed = 8

local ballDX = ballSpeed
local ballDY = -ballSpeed


local blocks = {}

local blockRows = 6
local blockCols = 15
local blockWidth = 63
local blockHeight = 20
local blockPadding = 5
local blockOffsetTop = 10
local blockOffsetLeft = 4
local blockRowColors = 
{
    0x004848C8, -- top
    0x003A6CC6,
    0x00307AB4,
    0x002AA2A2,
    0x0048A048,
    0x00C84842,  -- bottom
}

blockRows = 3;
blockWidth = 20;
blockHeight = 110;

local function ResetBall()
    print("Reset ball")

    ballX = math.floor(paddleX + paddleWidth / 2)
    ballY = paddleY - paddleHeight - 1
    ballDX = math.abs(ballSpeed)
    ballDY = -math.abs(ballSpeed)

end
 
local function ResetGame()
    print("Reset Game")
    
    hasWon = false
    hasLost = false

    local winW = GameEngine:GetWidth()
    local winH = GameEngine:GetHeight()
    paddleX = math.floor((winW - paddleWidth) / 2)
    paddleY = math.floor(winH - paddleHeight - 180)

    ResetBall()

    for c = 1, blockCols do
        blocks[c] = {}
        for r = 1, blockRows do
            blocks[c][r] = { x = 0, y = 0, alive = true }
        end
    end


end


function BeginGame()
    print("Lua: Game Begin")
end


function DestroyGame()
    print("Lua: Game Destroy")
end


function InitializeGame()
    print("Lua: Initializing Game")
    GameEngine:SetTitle("LuaGame: Breakout")

    ResetGame()

end


function GameStart()
    print("Lua: Game Start")
end


function GameEnd()
    print("Lua: Game End")
end


function Paint(rect)
    GameEngine:SetColor(0x331c18)
    GameEngine:FillRect(0, 0, rect.right, rect.bottom)

    for c = 1, blockCols do
        for r = 1, blockRows do
            local b = blocks[c][r]
            if b.alive then
                local blockX = (c - 1)*(blockWidth + blockPadding) + blockOffsetLeft
                local blockY = (r - 1)*(blockHeight + blockPadding) + blockOffsetTop
                GameEngine:SetColor(blockRowColors[r])
                GameEngine:FillRect(blockX, blockY, blockX + blockWidth, blockY + blockHeight)
            end
        end
    end
    

    GameEngine:SetColor(grayColor)
    GameEngine:FillRect(paddleX, paddleY, paddleX + paddleWidth, paddleY + paddleHeight)
    GameEngine:FillOval(ballX - ballRadius, ballY + ballRadius, ballX + ballRadius, ballY - ballRadius)


    -- like of fading game out with a small opacity
    if hasLost then
        GameEngine:SetColor(0x331c18)
        GameEngine:FillRect(0, 0, rect.right, rect.bottom, 0.5)


    end

    if hasWon then
        GameEngine:SetColor(0x331c18)
        GameEngine:FillRect(0, 0, rect.right, rect.bottom, 0.2)


    end



end


function Tick()

    if hasLost then 
        return
    end

    local winW = GameEngine:GetWidth()
    local winH = GameEngine:GetHeight()

    ballX = ballX + ballDX
    ballY = ballY + ballDY


    if ballX - ballRadius <= 0 or ballX + ballRadius >= winW then
        print("ball hit side walls")
        ballDX = -ballDX
    end

    if ballY - ballRadius <= 0 then
        print("ball hit top")
        ballDY = -ballDY
    end

    if ballY + ballRadius >= winH then
        print("ball hit bottom")
        hasLost = true
        --ResetBall()
    end


    if ballY + ballRadius >= paddleY and ballX >= paddleX and ballX <= paddleX + paddleWidth then
        ballDY = -math.abs(ballDY)
    end


    for c = 1, blockCols do
        for r = 1, blockRows do
            local b = blocks[c][r]
            if b.alive then
                local blockX = (c - 1)*(blockWidth + blockPadding) + blockOffsetLeft
                local blockY = (r - 1)*(blockHeight + blockPadding) + blockOffsetTop

                if ballX + ballRadius >= blockX and ballX - ballRadius <= blockX + blockWidth and
                   ballY + ballRadius >= blockY and ballY - ballRadius <= blockY + blockHeight then
                    ballDY = -ballDY
                    b.alive = false
                end
            end
        end
    end

    CheckKeyKeyboard()

end


function CheckKeyKeyboard()
    if hasLost or hasWon then
        if GameEngine:IsKeyDown(32) then -- space bar
            ResetGame()
        end

        return
    end

    if GameEngine:IsKeyDown(65) then -- A key
        paddleX = paddleX - paddleSpeed
    end
    if GameEngine:IsKeyDown(68) then -- D key
        paddleX = paddleX + paddleSpeed
    end

    local winW = GameEngine:GetWidth()
    if paddleX < 0 then
        paddleX = 0
    elseif paddleX + paddleWidth > winW then
        paddleX = winW - paddleWidth
    end

end


function MouseButtonAction(button, x, y)
end


function MouseWheelAction(delta, x, y)
end


function MouseMove(x, y)
end


function KeyPressed(key)
    print("Lua: Key pressed", key)
end


function CallAction(action)
    print("Lua: Action called", action)
end




