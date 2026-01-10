#include "Editor.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "rlImGui.h"
#include "Core/Engine.h"
#include "Core/Log.h"

namespace Micro
{
    #define DEFAULT_EDITOR_SCREEN_WIDTH 1280
    #define DEFAULT_EDITOR_SCREEN_HEIGHT 720

    Editor::Editor()
    {
        int screenWidth = DEFAULT_EDITOR_SCREEN_WIDTH;
        int screenHeight = DEFAULT_EDITOR_SCREEN_HEIGHT;

        MWindow::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
        MWindow::Init(screenWidth, screenHeight, "Micro Engine");
        m_Window.SetTargetFPS(60);

        std::string exeDir = GetApplicationDirectory();
        std::string imguiIni = exeDir + "imgui.ini";
        std::string defaultIni = exeDir + "default.ini";

        ImFileHandle iniFile = ImFileOpen(imguiIni.c_str(), "rb");
        bool isFirstLaunch = iniFile == nullptr;
        if (iniFile != nullptr)
        {
            ImFileClose(iniFile);
        }

        rlImGuiSetup(true);
        ImGui::GetIO().IniFilename = strdup(imguiIni.c_str());
        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        if (isFirstLaunch)
        {
            ImGui::LoadIniSettingsFromDisk(defaultIni.c_str());
        }

        m_SceneView.Init(screenWidth, screenHeight);

        MICRO_LOG_INFO("Editor App Initialized");
    }

    Editor::~Editor() {}

    int Editor::Run(Engine* engine)
    {
        m_Engine = engine;

        while (!MWindow::ShouldClose() && !m_ShouldShutdown)
        {
            if (m_FocusedView == EditorView::Scene)
            {
                m_SceneView.Update();
            }

            m_SceneView.Render(m_LastSceneViewSize);

            m_Window.BeginDrawing();
            m_Window.ClearBackground(DARKGRAY);
            rlImGuiBegin();

            DrawMenuBar();
            DrawMainViewport(m_SceneView.GetRenderTexture());

            rlImGuiEnd();
            m_Window.EndDrawing();
        }

        rlImGuiShutdown();

        return 0;
    }

    void Editor::DrawMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open"))
                {
                }

                if (ImGui::MenuItem("Quit"))
                {
                    m_ShouldShutdown = true;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Reset Layout"))
                {
                    std::string exeDir = GetApplicationDirectory();
                    std::string defaultIni = exeDir + "default.ini";
                    ImGui::LoadIniSettingsFromDisk(defaultIni.c_str());
                }

                if (ImGui::MenuItem("Save Layout"))
                {
                    std::string exeDir = GetApplicationDirectory();
                    std::string defaultIni = exeDir + "default.ini";
                    ImGui::SaveIniSettingsToDisk(defaultIni.c_str());
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void Editor::DrawMainViewport(MRenderTexture* sceneViewRT)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::DockSpaceOverViewport(0, viewport, ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar))
        {
            ImVec2 size = ImGui::GetContentRegionAvail();
            bool resized = (size.x != m_LastSceneViewSize.x || size.y != m_LastSceneViewSize.y);
            if (resized)
            {
                m_SceneView.Resize(size.x, size.y);
                m_LastSceneViewSize = size;
            }

            rlImGuiImageRenderTextureFit(sceneViewRT, true);

            if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
            {
                m_FocusedView = EditorView::Scene;
            }
        }
        ImGui::End();
        ImGui::PopStyleVar();

        if (ImGui::Begin("Hierarchy"))
        {
            if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
            {
                m_FocusedView = EditorView::Hierarchy;
            }
        }
        ImGui::End();

        if (ImGui::Begin("Inspector"))
        {
            if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
            {
                m_FocusedView = EditorView::Inspector;
            }
        }
        ImGui::End();

        if (ImGui::Begin("Project"))
        {
            if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
            {
                m_FocusedView = EditorView::Project;
            }
        }
        ImGui::End();

        if (ImGui::Begin("Console"))
        {
            m_ConsoleView.Render();

            if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
            {
                m_FocusedView = EditorView::Console;
            }
        }
        ImGui::End();
    }
}  // namespace Micro
