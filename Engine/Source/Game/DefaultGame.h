#pragma once

#include "GameBase.h"

namespace Micro
{
    class DefaultGame : public GameBase
    {
    public:
        explicit DefaultGame();

        void OnInit() override;
        void OnUpdate(float deltaTime) override;
        void OnShutdown() override;

    private:
        GameObject* m_cubeObject = nullptr;
    };
}  // namespace Micro
