#pragma once

#include "raylib-cpp.hpp"
#include "imgui.h"
#include "Core/View/SceneView.h"

namespace Micro
{
class EditorApp
{
public:
    EditorApp();
    int Run();

private:
    raylib::Window m_window;
    SceneView m_sceneView;

    ImVec2 m_lastSceneViewSize;
    bool m_shouldShutdown = false;

    void DrawMenuBar();
    void DrawMainViewport(raylib::RenderTexture* renderTexture);
};
}  // namespace Micro