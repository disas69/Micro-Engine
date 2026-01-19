#pragma once

#include "System.h"

namespace Micro
{
    class UpdateSystem : public System
    {
        void Process(GameBase* game) override;
    };
}  // namespace Micro
