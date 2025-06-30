print("GameEngine.lua")
print("Very Cool :D")

local fps <const> = 144
local deltaTime <const> = 1 / fps

local hasWon = false
local hasLost = false
local isBallLaunched = false

local grayColor = 0x00F0F0F0

local paddleX = 0
local paddleY = 0
local paddleWidth = 175
local paddleHeight = 20
local paddleSpeed = 300

local ballX = 0
local ballY = 0
local ballRadius = 15
local ballSpeed = 550

local ballDX = ballSpeed
local ballDY = -ballSpeed


local blocks = {}

local blockRows = 6
local blockCols = 15
local blockWidth = 63
local blockHeight = 35
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

local centerX = 0
local centerY = 0



local function ResetBall()
    --print("Reset ball")

    ballX = paddleX + paddleWidth / 2
    ballY = paddleY - ballRadius
    ballDX = 0
    ballDY = 0

    isBallLaunched = false
end
 
local function ResetGame()
    --print("Reset Game")
    
    hasWon = false
    hasLost = false

    local winW = GameEngine:GetWidth()
    local winH = GameEngine:GetHeight()
    paddleX = (winW - paddleWidth) / 2
    paddleY = winH - paddleHeight - 180

    ResetBall()

    for column = 1, blockCols do
        blocks[column] = {}
        for row = 1, blockRows do
            blocks[column][row] = { x = 0, y = 0, alive = true }
        end
    end


end


function InitializeGame()
    --print("Lua: Initializing Game")
    GameEngine:SetTitle("LuaGame: Breakout")
    GameEngine:SetFrameRate(fps)

    centerX = math.floor(GameEngine:GetWidth() / 2)
    centerY = math.floor(GameEngine:GetHeight() / 2)

    ResetGame()

end


function Paint(rect)
    GameEngine:SetColor(0x331c18)
    GameEngine:FillRect(0, 0, rect.right, rect.bottom)

    for column = 1, blockCols do
        for row = 1, blockRows do
            local block = blocks[column][row]
            if block.alive then
                local blockX = (column - 1) * (blockWidth + blockPadding) + blockOffsetLeft
                local blockY = (row - 1) * (blockHeight + blockPadding) + blockOffsetTop

                GameEngine:SetColor(blockRowColors[row])
                GameEngine:FillRect(blockX, blockY, blockX + blockWidth, blockY + blockHeight)
            end
        end
    end
    

    GameEngine:SetColor(grayColor)
    GameEngine:FillRect(math.floor(paddleX), math.floor(paddleY), math.floor(paddleX + paddleWidth), math.floor(paddleY + paddleHeight))
    GameEngine:FillOval(math.floor(ballX - ballRadius), math.floor(ballY + ballRadius), math.floor(ballX + ballRadius), math.floor(ballY - ballRadius))


    -- like of fading game out with a small opacity
    if hasLost then
        GameEngine:SetColor(0x331c18)
        GameEngine:FillRect(0, 0, rect.right, rect.bottom, 100)

        GameEngine:SetColor(grayColor)

        GameEngine:SetFontSize(90)
        GameEngine:DrawString("Lost Game", centerX - 196, centerY - 50)

        GameEngine:SetFontSize(40)
        GameEngine:DrawString("Press R To Restart", centerX - 182, centerY + 30)

    end

    if hasWon then
        GameEngine:SetColor(0x331c18)
        GameEngine:FillRect(0, 0, rect.right, rect.bottom, 100)
        
        GameEngine:SetColor(grayColor)

        GameEngine:SetFontSize(90)
        GameEngine:DrawString("Won Game", centerX - 203, centerY - 50)

        GameEngine:SetFontSize(40)
        GameEngine:DrawString("Press R To Play Again", centerX - 172, centerY + 30)

    end

    if not isBallLaunched then
        GameEngine:SetColor(grayColor)
        GameEngine:SetFontSize(40)

        local winH = GameEngine:GetHeight()
        GameEngine:DrawString("Press Space To launch Ball", centerX - 196, winH - 100)
    end


end


function Tick()

    if hasLost or hasWon or not isBallLaunched then 
        return
    end

    local areAllBlocksDestroyed = true

    for column = 1, blockCols do
        for row = 1, blockRows do
            if blocks[column][row].alive then
                areAllBlocksDestroyed = false
                break
            end
        end
        if not areAllBlocksDestroyed then
            break
        end
    end

    if areAllBlocksDestroyed then
        hasWon = true
    end


    local winW = GameEngine:GetWidth()
    local winH = GameEngine:GetHeight()

    ballX = ballX + ballDX * deltaTime
    ballY = ballY + ballDY * deltaTime


    if ballX - ballRadius <= 0 or ballX + ballRadius >= winW then
        --print("ball hit side walls")
        ballDX = -ballDX
    end

    if ballY - ballRadius <= 0 then
        --print("ball hit top")
        ballDY = -ballDY
    end

    if ballY + ballRadius >= winH then
        --print("ball hit bottom")
        hasLost = true
    end

    -- ball collision with paddle
    if ballY + ballRadius >= paddleY and ballY - ballRadius < paddleY and ballX + ballRadius >= paddleX and ballX - ballRadius <= paddleX + paddleWidth then
        ballDY = -math.abs(ballDY)
    end


    for column = 1, blockCols do
        for row = 1, blockRows do
            local block = blocks[column][row]
            if block.alive then
                local blockX = (column - 1) * (blockWidth + blockPadding) + blockOffsetLeft
                local blockY = (row - 1) * (blockHeight + blockPadding) + blockOffsetTop
                
                if ((ballX + ballRadius >= blockX) and (ballX - ballRadius <= blockX + blockWidth) and
                    (ballY + ballRadius >= blockY) and (ballY - ballRadius <= blockY + blockHeight)) then

                    -- find the closest X/Y to the ball on the block
                    local closestX = math.max(blockX, math.min(blockX + blockWidth, ballX))
                    local closestY = math.max(blockY, math.min(blockY + blockHeight, ballY)) 

                    local distanceToBallX = ballX - closestX 
                    local distanceToBallY = ballY - closestY

                    local distanceToBall = math.sqrt(distanceToBallX ^ 2 + distanceToBallY ^ 2) -- cool, they have the caret/power of operator 

                    if distanceToBall <= ballRadius then
                        local overlappingLeft = (ballX + ballRadius) - blockX;
                        local overlappingRight = -(ballX - ballRadius) + (blockX + blockWidth);
                        local overlappingBottom = -(ballY - ballRadius) + (blockY + blockHeight);
                        local overlappingTop = (ballY + ballRadius) - blockY;

                        -- the one with the least overlapping length is where the real overlapping happened
                        local minOverlappingLength = math.min(overlappingLeft, overlappingRight, overlappingBottom, overlappingTop)

                        
                        if minOverlappingLength == overlappingLeft or minOverlappingLength == overlappingRight then
                            --print("Hit Right/Left of Block")                            
                            ballDX = -ballDX
                        end
 
                        if minOverlappingLength == overlappingBottom or minOverlappingLength == overlappingBottom then
                            --print("Hit Bottom/Top of Block")                            
                            ballDY = -ballDY
                        end

                    end
                   
                    block.alive = false
                    goto doneCollisions -- cool, jmp
                end
            end
        end
    end

    ::doneCollisions::

    CheckKeyKeyboard()

end


function CheckKeyKeyboard()
    if hasLost or hasWon then
        if GameEngine:IsKeyDown(82) then -- R key
            ResetGame()
        end
        return
    end

    if not isBallLaunched then
        if GameEngine:IsKeyDown(32) then  -- space bar
            isBallLaunched = true

            ballDX = ballSpeed 
            ballDY = -ballSpeed 

            local randomAngle = 0
            if math.random() < 0.5 then
                randomAngle = math.rad(45 + math.random() * 25) --45-70
            else
                randomAngle = math.rad(110 + math.random() * 25) -- 110-135
            end

            ballDX = ballSpeed * math.cos(randomAngle)
            ballDY = -ballSpeed * math.sin(randomAngle)

        end
        return
    end

    if GameEngine:IsKeyDown(65) then -- A key
        paddleX = paddleX - paddleSpeed * deltaTime
    end
    if GameEngine:IsKeyDown(68) then -- D key
        paddleX = paddleX + paddleSpeed * deltaTime
    end

    local winW = GameEngine:GetWidth()
    if paddleX < 0 then
        paddleX = 0
    elseif paddleX + paddleWidth > winW then
        paddleX = winW - paddleWidth
    end

end

--[[

function MouseButtonAction(button, x, y)
end


function MouseWheelAction(delta, x, y)
end


function MouseMove(x, y)
end


function KeyPressed(key)
    --print("Lua: Key pressed", key)
end


function CallAction(action)
    --print("Lua: Action called", action)
end

]]


