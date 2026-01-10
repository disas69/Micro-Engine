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
        Engine* m_Engine = nullptr;

        MWindow m_Window;
        SceneView m_SceneView;
        ConsoleView m_ConsoleView;

        EditorView m_FocusedView = EditorView::None;

        ImVec2 m_LastSceneViewSize;
        bool m_ShouldShutdown = false;

        void DrawMenuBar();
        void DrawMainViewport(MRenderTexture* sceneViewRT);
    };
}  // namespace Micro