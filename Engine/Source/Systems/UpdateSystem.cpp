#include "UpdateSystem.h"

namespace Micro
{
    void UpdateSystem::Process(GameBase* game)
    {
        game->Update(GetFrameTime());
    }
}  // namespace Micro
