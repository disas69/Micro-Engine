#pragma once

#include "Game/GameBase.h"

namespace Micro
{
    enum class SystemPhase : uint8_t
    {
        OnInit,
        OnPreUpdate,
        OnUpdate,
        OnPostUpdate,
        OnPreRender,
        OnRender,
        OnPostRender,
        OnShutdown
    };

    class System
    {
    public:
        virtual ~System() = default;
        virtual void Process(GameBase* game) = 0;
    };
}  // namespace Micro
