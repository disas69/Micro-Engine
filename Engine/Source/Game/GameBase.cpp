#include "GameBase.h"
#include "Gameplay/GameObject.h"

using namespace Micro;

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
    for (auto* gameObject : m_gameObjects)
    {
        gameObject->OnUpdate(deltaTime);
    }
}

void GameBase::Render3DGameObjects()
{
    for (auto* gameObject : m_gameObjects)
    {
        gameObject->OnRender3D();
    }
}

void GameBase::Render2DGameObjects()
{
    for (auto* gameObject : m_gameObjects)
    {
        gameObject->OnRender2D();
    }
}

void GameBase::RenderUIGameObjects()
{
    for (auto* gameObject : m_gameObjects)
    {
        gameObject->OnRenderUI();
    }
}
