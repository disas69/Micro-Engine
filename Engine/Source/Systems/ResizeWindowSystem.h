#pragma once

#include "System.h"

namespace Micro
{
    class ResizeWindowSystem : public System
    {
    public:
        void Process(GameBase* game) override;
    };
}  // namespace Micro
