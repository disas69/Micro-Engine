#pragma once

#include "GameBase.h"

namespace Micro
{
class DefaultGame : public GameBase
{
public:
    explicit DefaultGame(ArenaAllocator& persistentArena);

    void OnInit() override;
    void Update(ArenaAllocator& frameArena, float deltaTime) override;
    void Render() override;

private:
    raylib::Camera m_camera = {};

    GameObject* m_2dGameObject = nullptr;
    GameObject* m_3dGameObject = nullptr;
};
}  // namespace Micro
