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
        GameObject* m_imageObject = nullptr;
        GameObject* m_textObject = nullptr;
        float m_time = 0.0f;
    };
}  // namespace Micro
