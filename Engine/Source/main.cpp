#include "Core/Engine.h"
#include "Game/DefaultGame.h"
#include "Game/GameBase.h"

int main()
{
    Micro::Engine engine;
    Micro::DefaultGame game;
    return engine.Run(&game);
}