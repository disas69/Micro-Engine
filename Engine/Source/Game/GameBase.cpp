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
        if (m_Scene != nullptr)
        {
            m_Scene->Update(deltaTime);
        }

        OnUpdate(deltaTime);
    }

    void GameBase::Shutdown()
    {
        OnShutdown();
    }
}  // namespace Micro