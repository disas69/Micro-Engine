#include "Core/Engine.h"
#include "Game/DefaultGame.h"
#include "Game/GameBase.h"

int main()
{
    Micro::Engine engine;

    auto game = std::make_unique<Micro::DefaultGame>();

    // TODO: Load game.ini or create new, init game settings

    return engine.Run(game.get());
}