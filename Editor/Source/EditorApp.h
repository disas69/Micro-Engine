#pragma once

#include <cstdint>
#include "raylib-cpp.hpp"
#include "imgui.h"
#include "Core/Engine.h"
#include "Core/View/SceneView.h"

enum class EditorView : uint8_t
{
    None = 0,
    Scene = 1,
    Hierarchy = 2,
    Inspector = 3,
    Project = 4,
    Console = 5
};

namespace Micro
{
class EditorApp
{
public:
    EditorApp();
    int Run();

private:
    Engine m_engine;
    raylib::Window m_window;

    SceneView m_sceneView;

    EditorView m_focusedView = EditorView::None;

    ImVec2 m_lastSceneViewSize;
    bool m_shouldShutdown = false;

    void DrawMenuBar();
    void DrawMainViewport(raylib::RenderTexture* sceneViewRT);
};
}  // namespace Micro