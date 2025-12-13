#include "Engine.h"
#include "Log.h"

using namespace Micro;

Engine::Engine()
{
    Log::Initialize();
    Log::Info("Initializing Micro Engine. Version: " + std::string(version()));
}

int Engine::Run()
{
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Window::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    raylib::Window::Init(screenWidth, screenHeight, "raylib-cpp - basic window");
    m_window.SetTargetFPS(60);

    while (!m_window.ShouldClose())
    {
        m_window.BeginDrawing();
        m_window.ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        m_window.EndDrawing();
    }

    return 0;
}