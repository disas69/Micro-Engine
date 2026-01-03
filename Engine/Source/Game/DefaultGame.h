#pragma once

#include "GameBase.h"

namespace Micro
{
class DefaultGame : public GameBase
{
public:
    explicit DefaultGame(ArenaAllocator& persistentArena);

    void OnInit() override;
    void OnUpdate(ArenaAllocator& frameArena, float deltaTime) override;
    void OnRender() override;

private:
    raylib::Camera m_camera;

    GameObject* m_2dGameObject = nullptr;
    GameObject* m_3dGameObject = nullptr;
    GameObject* m_textGameObject = nullptr;
    GameObject* m_imageGameObject = nullptr;
    GameObject* m_buttonGameObject = nullptr;
};
}  // namespace Micro
