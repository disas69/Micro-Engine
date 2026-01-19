#include "LateUpdateSystem.h"

namespace Micro
{
    void LateUpdateSystem::Process(GameBase* game)
    {
        game->LateUpdate(GetFrameTime());
    }
}  // namespace Micro