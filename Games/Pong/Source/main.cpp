#include "Core/Engine.h"
#include "PongGame.h"

int main()
{
    Micro::Engine engine;
    Pong::PongGame game;
    return engine.Run(&game);
}