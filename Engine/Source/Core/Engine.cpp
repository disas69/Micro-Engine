#include "Engine.h"
#include "Log.h"
#include "Game/GameBase.h"
#include "Gameplay/Components/CameraComponent.h"
#include "Gameplay/Components/ImageComponent.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/PrimitiveMeshComponent.h"
#include "Gameplay/Components/SpriteComponent.h"
#include "Gameplay/Components/TextComponent.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Services/ServiceLocator.h"
#include "Services/SceneService.h"
#include "Services/SettingsService.h"
#include "Services/AssetsService.h"
#include "Systems/SystemRegistry.h"
#include "Systems/InitSystem.h"
#include "Systems/LateUpdateSystem.h"
#include "Systems/UpdateSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/ResizeWindowSystem.h"
#include "Systems/ShutdownSystem.h"
#include "Systems/TransformSystem.h"
#include "Settings/ProjectSettings.h"

namespace Micro
{
    Engine::Engine()
    {
        Log::Initialize();

        MICRO_LOG_INFO("Initializing Micro Engine. Version: " + std::string(version()));

        // Register services
        ServiceLocator::Register(std::make_unique<SettingsService>());
        ServiceLocator::Register(std::make_unique<AssetsService>());
        ServiceLocator::Register(std::make_unique<SceneService>());

        // Register components
        TypeRegistry::Register(&TransformComponent::GetType());
        TypeRegistry::Register(&CameraComponent::GetType());
        TypeRegistry::Register(&MeshComponent::GetType());
        TypeRegistry::Register(&PrimitiveMeshComponent::GetType());
        TypeRegistry::Register(&SpriteComponent::GetType());
        TypeRegistry::Register(&ImageComponent::GetType());
        TypeRegistry::Register(&TextComponent::GetType());

        // Register systems
        // OnInit
        SystemRegistry::Register<InitSystem>(SystemPhase::OnInit);

        // OnPreUpdate
        // ...

        // OnUpdate
        SystemRegistry::Register<UpdateSystem>(SystemPhase::OnUpdate);

        // OnPostUpdate
        SystemRegistry::Register<TransformSystem>(SystemPhase::OnPostUpdate);
        SystemRegistry::Register<LateUpdateSystem>(SystemPhase::OnPostUpdate);

        // OnPreRender
        // ...

        // OnRender
        SystemRegistry::Register<RenderSystem>(SystemPhase::OnRender);

        // OnPostRender
        SystemRegistry::Register<ResizeWindowSystem>(SystemPhase::OnPostRender);

        // OnShutdown
        SystemRegistry::Register<ShutdownSystem>(SystemPhase::OnShutdown);
    }

    Engine::~Engine()
    {
        MICRO_LOG_INFO("Shutting down Micro Engine.");
        Shutdown();
    }

    int Engine::Run()
    {
        GameBase* game = m_Game.get();

        if (game == nullptr)
        {
            MICRO_LOG_ERROR("Game is not loaded");
            return 1;
        }

        ServiceLocator::Get<AssetsService>()->ScanAssets();

        // Init phase
        auto projectSettings = ServiceLocator::Get<SettingsService>()->LoadOrDefault<ProjectSettings>();

        MWindow::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
        MWindow::Init(projectSettings.WindowWidth, projectSettings.WindowHeight, game->GetWindowTitle());
        m_Window.SetTargetFPS(projectSettings.TargetFPS);

        SystemRegistry::Process(SystemPhase::OnInit, game);

        while (!MWindow::ShouldClose() && !game->ShouldClose())
        {
            // Update phase
            SystemRegistry::Process(SystemPhase::OnPreUpdate, game);
            SystemRegistry::Process(SystemPhase::OnUpdate, game);
            SystemRegistry::Process(SystemPhase::OnPostUpdate, game);

            // Render phase
            m_Window.BeginDrawing();
            m_Window.ClearBackground(RAYWHITE);

            SystemRegistry::Process(SystemPhase::OnPreRender, game);
            SystemRegistry::Process(SystemPhase::OnRender, game);
            SystemRegistry::Process(SystemPhase::OnPostRender, game);

            m_Window.EndDrawing();
        }

        // Shutdown phase
        SystemRegistry::Process(SystemPhase::OnShutdown, game);

        return 0;
    }

    void Engine::Shutdown()
    {
        ServiceLocator::Shutdown();
    }
}  // namespace Micro
