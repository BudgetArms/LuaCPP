---@meta
--- This file provides type annotations for Lua scripts interacting with C++ via SOL2.

GameEngine = {}


--- # Sets the title of the window
--- # @param title String # the title string
--- # @return nil
function GameEngine:SetTitle(title) end


--- Sets the window position x and y
--- @param x number # The x-coordinate.
--- @param y number # The y-coordinate.
--- @return nil
function GameEngine:SetWindowPosition(x, y) end


--- Set key list ???
--- @param keyList String # framerate number
--- @return nil
function GameEngine:SetKeyList(keyList) end


--- Set/Changes the frame rate
--- @param frameRate number # framerate number
--- @return nil
function GameEngine:SetFrameRate(frameRate) end


--- Set the window width
--- @param width number
--- @return nil
function GameEngine:SetWidth(width) end


--- Set the window height
--- @param height number
--- @return nil
function GameEngine:SetHeight(height) end


--- Go fullscreen
--- @return boolean
function GameEngine:GoFullScreen() end


--- Go windowed
--- @return boolean
function GameEngine:GoWindowedMode() end


--- Set mouse pointer visibility
--- @param value bool
--- @return nil
function GameEngine:SetMouseVisibility(value) end


--- Quit the application
--- @return nil
function GameEngine:Quit() end


--- return if it has window region
--- @return boolean
function GameEngine:HasWindowRegion() end


--- is fullscreen
--- @return boolean
function GameEngine:IsFullscreen() end


--- bool iskeydown
--- @param vKey number # keycode of key
--- @return boolean
function GameEngine:IsKeyDown(vKey) end


--- Display a message box 
--- @param message String # tstring message
--- @return nil
function GameEngine:MessageBox(message) end

--- fucked, I dont want this
--- Display a message box (with tchar, lmao)
--- @param message String # tstring message
--- @return nil
---function GameEngine:MessageBoxC(message) end




--- sets with rgb
--- Sets the color of drawing thing 
--- @param r number 
--- @param g number
--- # @param b number
--- @return nil
---function GameEngine:SetColor(r, g, b) end


--- sets with 0x00BBGGRR
--- Sets the color of drawing thing 
--- @param color String 
--- @return nil
function GameEngine:SetColor(color) end
 

--- Sets the font of the text 
--- @return nil
function GameEngine:SetFont(font) end
 

--- Sets the size of the current text font 
--- @return nil
function GameEngine:SetFontSize(size) end


--- draw line 
--- @param x1 number
--- @param y1 number
--- @param x2 number
--- @param y2 number
--- @return boolean
function GameEngine:DrawLine(x1, y1, x2, y2) end


--- draw rect 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top	  number
--- @return boolean
function GameEngine:DrawRect(left, top, right, bottom) end


--- fill rect 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @return boolean
function GameEngine:FillRect(left, top, right, bottom) end


--- fill rect 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @param opacity    number
--- @return boolean
function GameEngine:FillRect(left, top, right, bottom, opacity) end


--- draw round rect 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top	  number
--- @param radius	  number
--- @return boolean
function GameEngine:DrawRoundRect(left, top, right, bottom, radius) end


--- fill round rect 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @param radius number
--- @return boolean
function GameEngine:FillRoundRect(left, top, right, bottom, radius) end


--- Draw oval
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @return boolean
function GameEngine:DrawOval(left, top, right, bottom) end


--- fill oval 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @return boolean
function GameEngine:FillOval(left, top, right, bottom) end

 
--- fill oval 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @param opacity number
--- @return boolean
function GameEngine:FillOval(left, top, right, bottom, opacity) end


--- draw arc 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @param startDegree number
--- @param angle number
--- @return boolean
function GameEngine:DrawArc(left, top, right, bottom, startDegree, angle) end


--- Fill arc 
--- @param left   number
--- @param bottom number
--- @param right  number
--- @param top    number
--- @param startDegree number
--- @param angle number
--- @return boolean
function GameEngine:FillArc(left, top, right, bottom, startDegree, angle) end


--- Draw String at point
--- @param text String
--- @param left number
--- @param top number
function GameEngine::DrawString(text, left, top)


--- Draw String in rect
--- @param text String
--- @param left number
--- @param top number
--- @param right number
--- @param bottom number
--- @return number
function GameEngine::DrawString(text, left, top, right, bottom)


--- Repaint??
--- @return boolean
function GameEngine::Repaint() end


--- get the window title
--- @return string
function GameEngine::GetTitle() end


--- Gets the width of the window
--- @return number
function GameEngine:GetWidth() end


--- Gets the height of the window
--- @return number
function GameEngine:GetHeight() end


--- Gets the frame rate
--- @return number
function GameEngine:GetFrameRate() end


--- Gets the frame delay
--- @return number
function GameEngine:GetFrameDelay() end




GameEngine = nil
