#include "GameBase.h"

namespace Micro
{
    void GameBase::Init(MVector2 screenSize)
    {
        SetScreenSize(screenSize);
        OnInit();
    }

    void GameBase::Update(float deltaTime)
    {
        if (m_scene != nullptr)
        {
            m_scene->Update(deltaTime);
        }

        OnUpdate(deltaTime);
    }
}  // namespace Micro