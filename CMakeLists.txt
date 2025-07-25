﻿cmake_minimum_required(VERSION 3.20)

project(LuaGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Avoid a timestamp warning for FetchContent
cmake_policy(SET CMP0135 NEW)


Include(FetchContent)

# Fetch LUA
FetchContent_Declare(
    lua
    URL https://github.com/marovira/lua/archive/refs/tags/5.4.4.tar.gz
)
FetchContent_MakeAvailable(lua)


# Fetch SOL2
FetchContent_Declare(
    sol2
    URL https://github.com/ThePhD/sol2/archive/refs/tags/v3.3.0.tar.gz
)
FetchContent_MakeAvailable(sol2)

# Fetch SDL2
FetchContent_Declare(
    sdl
    URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-2.30.9.tar.gz
)
FetchContent_MakeAvailable(sdl)


list(APPEND SOURCES 
    "Engine/GameWinMain.cpp" 
    "Engine/AbstractGame.cpp" 
    "Engine/GameEngine.cpp" 
    "Engine/Game.cpp" 
)

list(APPEND LUA_SOURCES 
    "Game_Breakout/Game.lua"
)

# Executable Target
add_executable(${PROJECT_NAME} WIN32 ${SOURCES}) 

#link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static lua::lua sol2)

#Include 
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE Engine)

add_definitions(-DUNICODE -D_UNICODE)


# Copy Lua Scripts
add_custom_target(CopyLuaScripts ALL
    COMMENT "Copying Lua scripts to output directory"
)

# copy from current dir to build dir
FOREACH(LUA_SOURCE IN LISTS LUA_SOURCES)
    add_custom_command(TARGET CopyLuaScripts POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/${LUA_SOURCE}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/${LUA_SOURCE})
ENDFOREACH()

# copy lua source to target
add_dependencies(CopyLuaScripts ${PROJECT_NAME})


