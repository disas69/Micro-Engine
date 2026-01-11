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

    void Engine::RegisterStandardComponents()
    {
        TypeRegistry::Register(&TransformComponent::GetType());
        TypeRegistry::Register(&CameraComponent::GetType());
        TypeRegistry::Register(&MeshComponent::GetType());
        TypeRegistry::Register(&SpriteComponent::GetType());
        TypeRegistry::Register(&ImageComponent::GetType());
        TypeRegistry::Register(&TextComponent::GetType());
    }

    int Engine::Run()
    {
        if (m_Game == nullptr)
        {
            MICRO_LOG_ERROR("Game is not loaded");
            return 1;
        }

        int screenWidth = 800;
        int screenHeight = 450;

        MWindow::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
        MWindow::Init(screenWidth, screenHeight, m_Game->GetWindowTitle());
        m_Window.SetTargetFPS(60);

        m_Game->Init(MVector2{(float)GetScreenWidth(), (float)GetScreenHeight()});

        while (!MWindow::ShouldClose() && !m_Game->ShouldClose())
        {
            float deltaTime = GetFrameTime();

            m_Game->Update(deltaTime);

            Render();

            if (MWindow::IsResized())
            {
                m_Game->SetScreenSize(MVector2{(float)GetScreenWidth(), (float)GetScreenHeight()});
            }
        }

        m_Game->Shutdown();

        return 0;
    }

    void Engine::Render()
    {
        if (m_Game == nullptr)
        {
            MICRO_LOG_ERROR("Game is not loaded");
            return;
        }

        m_Window.BeginDrawing();
        m_Window.ClearBackground(RAYWHITE);

        RenderSystem::Render(m_Game->GetMainCamera(), m_Game->GetScene());

        m_Window.EndDrawing();
    }
}  // namespace Micro
