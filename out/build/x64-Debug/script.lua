--- script_annotations.lua has the annotations EmmyLua annotations for the GameEngine

print("Script.lua:")
print("Cool :D")


--Tester = Flower.new()

--print("Test: ")
--print(Tester)

--print("SEEDS:", Tester:HowManySeeds() )

--Tester:ChangeSeeds(25)

--print("SEEDS:", Tester:HowManySeeds() )



Game.RunGame()  

print("Game", Game)

Game:SetTitle("COOL")
print("Game Title:", Game:GetTitle())

--Game:RunGame()  

Game:SetTitle("COOL")

Game:GoFullScreen(true)

Game:End()

print("END")
