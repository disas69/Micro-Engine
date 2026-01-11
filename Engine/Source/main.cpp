#include "Core/Engine.h"
#include "Game/DefaultGame.h"

int main()
{
    Micro::Engine engine;
    engine.Load<Micro::DefaultGame>();
    return engine.Run();
}