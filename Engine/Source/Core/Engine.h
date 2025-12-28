#pragma once

#include "EngineConfig.h"
#include "raylib-cpp.hpp"

namespace Micro
{
class ArenaAllocator;
}
namespace Micro
{
class GameBase;
}
namespace Micro
{
class Engine final
{
public:
    Engine();
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    int Run(GameBase* game, ArenaAllocator& frameArena);
    void Render(GameBase* game);

    static constexpr std::string_view version()
    {
        return ENGINE_VERSION_STRING;
    }

private:
    raylib::Window m_window;
};
}