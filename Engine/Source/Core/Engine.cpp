#include "Engine.h"
#include "Log.h"
#include "Game/GameBase.h"

using namespace Micro;

Engine::Engine()
{
    Log::Initialize();

    MICRO_LOG_INFO("Initializing Micro Engine. Version: " + std::string(version()));
}

Engine::~Engine()
{
    MICRO_LOG_INFO("Shutting down Micro Engine.");
}

int Engine::Run(GameBase* game, ArenaAllocator& frameArena)
{
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Window::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    raylib::Window::Init(screenWidth, screenHeight, game->GetWindowTitle());
    m_window.SetTargetFPS(60);

    game->Init();

    while (!raylib::Window::ShouldClose() && !game->ShouldClose())
    {
        frameArena.Reset();

        game->Update(frameArena, GetFrameTime());

        Render(game);

        if (raylib::Window::IsResized())
        {
            game->Resize(GetScreenWidth(), GetScreenHeight());
        }
    }

    frameArena.Reset();
    return 0;
}

void Engine::Render(GameBase* game)
{
    m_window.BeginDrawing();
    m_window.ClearBackground(RAYWHITE);

    game->Render();

    m_window.EndDrawing();
}