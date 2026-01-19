#pragma once

#include "System.h"

namespace Micro
{
    class ShutdownSystem : public System
    {
    public:
        void Process(GameBase* game) override;
    };
}  // namespace Micro
