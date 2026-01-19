#include "ResizeWindowSystem.h"
#include "Core/Types.h"

namespace Micro
{
    void ResizeWindowSystem::Process(GameBase* game)
    {
        if (MWindow::IsResized())
        {
            game->SetScreenSize(MVector2{(float)GetScreenWidth(), (float)GetScreenHeight()});
        }
    }
}  // namespace Micro