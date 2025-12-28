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
};
}  // namespace Micro
