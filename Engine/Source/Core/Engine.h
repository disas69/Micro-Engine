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
        MWindow m_Window;
        std::unique_ptr<Scene> m_ActiveScene;

        void RegisterStandardComponents();
        void Render(GameBase* game);
    };
}  // namespace Micro