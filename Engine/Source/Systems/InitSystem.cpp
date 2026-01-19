#include "InitSystem.h"
#include "Core/Types.h"

namespace Micro
{
    void InitSystem::Process(GameBase* game)
    {
        game->Init(MVector2{(float)GetScreenWidth(), (float)GetScreenHeight()});
    }
}  // namespace Micro
