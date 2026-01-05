#pragma once

#include "EngineConfig.h"
#include "Gameplay/Scene.h"

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

        static constexpr std::string_view version() { return ENGINE_VERSION_STRING; }

    private:
        void Render(GameBase* game);

        MWindow m_window;
        std::unique_ptr<Scene> m_activeScene;
    };
}  // namespace Micro