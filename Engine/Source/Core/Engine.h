#pragma once

#include "EngineConfig.h"
#include "Game/GameBase.h"
#include "Settings/ProjectSettings.h"

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

        template <typename T>
        void Load()
        {
            static_assert(std::is_base_of<GameBase, T>::value, "T must be derived from GameBase");

            m_Game = std::make_unique<T>();
            m_Game->RegisterCustomServices();
            m_Game->RegisterCustomComponents();
            m_Game->RegisterCustomSystems();
        }

        int Run();
        void Shutdown();

        static constexpr std::string_view version() { return ENGINE_VERSION_STRING; }

    private:
        MWindow m_Window;
        std::unique_ptr<GameBase> m_Game = nullptr;
        ProjectSettings m_ProjectSettings;
    };
}  // namespace Micro