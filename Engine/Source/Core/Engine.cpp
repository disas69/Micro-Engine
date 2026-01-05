#include "Engine.h"
#include "Log.h"
#include "Game/GameBase.h"
#include "Gameplay/Systems/RenderSystem.h"

namespace Micro
{
    Engine::Engine()
    {
        Log::Initialize();

        MICRO_LOG_INFO("Initializing Micro Engine. Version: " + std::string(version()));
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
        m_window.SetTargetFPS(60);

        // Temp
        m_activeScene = std::make_unique<Scene>();
        game->SetScene(m_activeScene.get());

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

    void Engine::Render(GameBase* game)
    {
        m_window.BeginDrawing();
        m_window.ClearBackground(RAYWHITE);

        RenderSystem::Render(game->GetMainCamera(), m_activeScene.get());

        m_window.EndDrawing();
    }
}  // namespace Micro
