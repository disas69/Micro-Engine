#pragma once

#include "EngineConfig.h"
#include "raylib-cpp.hpp"

namespace Micro
{
class GameBase;

class Engine final
{
public:
    Engine();
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    int Run(GameBase* game);
    void Render(GameBase* game);

    static constexpr std::string_view version() { return ENGINE_VERSION_STRING; }

private:
    MWindow m_window;
};
}  // namespace Micro