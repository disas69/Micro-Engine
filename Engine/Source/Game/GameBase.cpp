#include "GameBase.h"
#include "Gameplay/GameObject.h"

namespace Micro
{
void GameBase::Init()
{
    Resize(GetScreenWidth(), GetScreenHeight());
    OnInit();
}

void GameBase::Resize(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}

void GameBase::UpdateGameObjects(float deltaTime)
{
    for (const auto& gameObject : m_gameObjects)
    {
        gameObject->OnUpdate(deltaTime);
    }
}

void GameBase::Render3DGameObjects()
{
    for (const auto& gameObject : m_gameObjects)
    {
        gameObject->OnRender3D();
    }
}

void GameBase::Render2DGameObjects()
{
    for (const auto& gameObject : m_gameObjects)
    {
        gameObject->OnRender2D();
    }
}

void GameBase::RenderUIGameObjects()
{
    for (const auto& gameObject : m_gameObjects)
    {
        gameObject->OnRenderUI();
    }
}
}  // namespace Micro
