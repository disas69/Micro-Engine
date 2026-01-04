#include "Engine.h"
#include "Log.h"
#include "Game/GameBase.h"

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

    game->Init();

    while (!MWindow::ShouldClose() && !game->ShouldClose())
    {
        game->OnUpdate(GetFrameTime());

        Render(game);

        if (MWindow::IsResized())
        {
            game->Resize(GetScreenWidth(), GetScreenHeight());
        }
    }

    return 0;
}

void Engine::Render(GameBase* game)
{
    m_window.BeginDrawing();
    m_window.ClearBackground(RAYWHITE);

    game->OnRender();

    m_window.EndDrawing();
}
}  // namespace Micro
