#include "Engine.h"
#include "Log.h"
#include "Game/GameBase.h"
#include "Gameplay/Components/CameraComponent.h"
#include "Gameplay/Components/ImageComponent.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/SpriteComponent.h"
#include "Gameplay/Components/TextComponent.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Systems/RenderSystem.h"

namespace Micro
{
    Engine::Engine()
    {
        Log::Initialize();

        MICRO_LOG_INFO("Initializing Micro Engine. Version: " + std::string(version()));

        RegisterStandardComponents();
    }

    Engine::~Engine()
    {
        MICRO_LOG_INFO("Shutting down Micro Engine.");
    }

    int Engine::Run(GameBase* game)
    {
        int screenWidth = 800;
        int screenHeight = 450;

        MWindow::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
        MWindow::Init(screenWidth, screenHeight, game->GetWindowTitle());
        m_Window.SetTargetFPS(60);

        // Temp
        m_ActiveScene = std::make_unique<Scene>();
        game->SetScene(m_ActiveScene.get());

        game->Init(MVector2{(float)GetScreenWidth(), (float)GetScreenHeight()});

        while (!MWindow::ShouldClose() && !game->ShouldClose())
        {
            float deltaTime = GetFrameTime();
            game->Update(deltaTime);

            Render(game);

            if (MWindow::IsResized())
            {
                game->SetScreenSize(MVector2{(float)GetScreenWidth(), (float)GetScreenHeight()});
            }
        }

        game->Shutdown();

        return 0;
    }

    void Engine::RegisterStandardComponents()
    {
        TypeRegistry::Register(&TransformComponent::GetType());
        TypeRegistry::Register(&CameraComponent::GetType());
        TypeRegistry::Register(&MeshComponent::GetType());
        TypeRegistry::Register(&SpriteComponent::GetType());
        TypeRegistry::Register(&ImageComponent::GetType());
        TypeRegistry::Register(&TextComponent::GetType());
    }

    void Engine::Render(GameBase* game)
    {
        m_Window.BeginDrawing();
        m_Window.ClearBackground(RAYWHITE);

        RenderSystem::Render(game->GetMainCamera(), m_ActiveScene.get());

        m_Window.EndDrawing();
    }
}  // namespace Micro
