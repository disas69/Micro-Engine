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
    void OnRender() override;

private:
    MCamera3D m_camera;

    GameObject* m_spriteGameObject = nullptr;
    GameObject* m_3dGameObject = nullptr;
    GameObject* m_textGameObject = nullptr;
    GameObject* m_imageGameObject = nullptr;
    GameObject* m_buttonGameObject = nullptr;
};
}  // namespace Micro
