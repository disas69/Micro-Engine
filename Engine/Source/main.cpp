#include "Core/Engine.h"
#include "Game/DefaultGame.h"
#include "Game/GameBase.h"
#include "Memory/ArenaAllocator.h"

#define PERSISTENT_AREA_SIZE 1024  // 1 MB persistent arena
#define FRAME_AREA_SIZE 10         // 10 KB frame arena

int main()
{
    Micro::Engine engine;

    Micro::ArenaAllocator persistentArena(1024 * PERSISTENT_AREA_SIZE);
    Micro::ArenaAllocator frameArena(1024 * FRAME_AREA_SIZE);

    // TODO: Load game.ini or create new
    Micro::GameBase* game = persistentArena.Allocate<Micro::DefaultGame>(persistentArena);

    return engine.Run(game, frameArena);
}