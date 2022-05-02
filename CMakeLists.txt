cmake_minimum_required(VERSION 3.21.1)
project(igrica)

set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    include_directories(
            /opt/homebrew/Cellar/sdl2/2.0.20/include/SDL2
    )
    link_directories(
            /opt/homebrew/Cellar/sdl2/2.0.20/lib
    )
endif(APPLE)
if(WIN32)
   set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

    include_directories(
            C:/libs/SDL/SDL2-2.0.20/include
    )
    link_directories(
            C:/libs/SDL/SDL2-2.0.20/lib/x64
    )
    endif(WIN32)

add_executable(igrica
        main.cpp
        PLAYER/Player.cpp PLAYER/Player.h
        GAME/Game.cpp GAME/Game.h
        VECTOR2D/Vector2D.cpp VECTOR2D/Vector2D.h
        GAMEOBJECT/GameObject.cpp GAMEOBJECT/GameObject.h
        MAP/Map.cpp MAP/Map.h
        MENU/Menu.cpp MENU/Menu.h  NPC/Animal.cpp NPC/Animal.h NPC/Enemy.cpp NPC/Enemy.h)

target_link_libraries(igrica SDL2main SDL2)
