#pragma once

#include "System.h"

namespace Micro
{
    class InitSystem : public System
    {
    public:
        void Process(GameBase* game) override;
    };
}  // namespace Micro
