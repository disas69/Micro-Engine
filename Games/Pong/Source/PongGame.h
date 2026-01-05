#pragma once

#include "Game/GameBase.h"

namespace Pong
{
    class PongGame : public Micro::GameBase
    {
    public:
        PongGame();

        void OnInit() override;
        void OnUpdate(float deltaTime) override;
        void OnShutdown() override;
    };
}  // namespace Pong