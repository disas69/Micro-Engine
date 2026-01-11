#include "Core/Engine.h"
#include "PongGame.h"

int main()
{
    Micro::Engine engine;
    engine.Load<Pong::PongGame>();
    return engine.Run();
}