#pragma once

#include <cstdint>
#include "raylib-cpp.hpp"
#include "imgui.h"
#include "Core/Engine.h"
#include "Core/View/ConsoleView.h"
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
    class Editor
    {
    public:
        Editor();
        ~Editor();

        Editor(const Editor&) = delete;
        Editor& operator=(const Editor&) = delete;
        Editor(Editor&&) = delete;
        Editor& operator=(Editor&&) = delete;

        int Run(Engine* engine);

    private:
        Engine* m_engine = nullptr;

        MWindow m_window;
        SceneView m_sceneView;
        ConsoleView m_consoleView;

        EditorView m_focusedView = EditorView::None;

        ImVec2 m_lastSceneViewSize;
        bool m_shouldShutdown = false;

        void DrawMenuBar();
        void DrawMainViewport(MRenderTexture* sceneViewRT);
    };
}  // namespace Micro