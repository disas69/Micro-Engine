#include "ShutdownSystem.h"

namespace Micro
{
    void ShutdownSystem::Process(GameBase* game)
    {
        game->Shutdown();
    }
}  // namespace Micro