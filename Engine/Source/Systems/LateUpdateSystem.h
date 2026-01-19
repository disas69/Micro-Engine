#pragma once
#include "System.h"

namespace Micro
{
    class LateUpdateSystem : public System
    {
    public:
        void Process(GameBase* game) override;
    };
}  // namespace Micro
