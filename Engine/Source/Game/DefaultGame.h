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

    private:
        GameObject* m_CubeObject = nullptr;
        GameObject* m_ImageObject = nullptr;
        GameObject* m_TextObject = nullptr;
        float m_Time = 0.0f;
    };
}  // namespace Micro
