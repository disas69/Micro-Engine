#include "EditorApp.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "rlImGui.h"
#include "Core/Engine.h"
#include "Core/Log.h"

using namespace Micro;

#define DEFAULT_EDITOR_SCREEN_WIDTH 1280
#define DEFAULT_EDITOR_SCREEN_HEIGHT 720

EditorApp::EditorApp()
{
    int screenWidth = DEFAULT_EDITOR_SCREEN_WIDTH;
    int screenHeight = DEFAULT_EDITOR_SCREEN_HEIGHT;

    raylib::Window::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    raylib::Window::Init(screenWidth, screenHeight, "Micro Engine");
    m_window.SetTargetFPS(60);

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
    ImGui::GetIO().FontGlobalScale = 1.2f;

    if (isFirstLaunch)
    {
        ImGui::LoadIniSettingsFromDisk(defaultIni.c_str());
    }

    m_sceneView.Init(screenWidth, screenHeight);

    Log::Info("Editor App Initialized");
}

int EditorApp::Run()
{
    while (!raylib::Window::ShouldClose() && !m_shouldShutdown)
    {
        if (m_focusedView == EditorView::Scene)
        {
            m_sceneView.Update();
        }

        m_sceneView.Render();

        m_window.BeginDrawing();
        m_window.ClearBackground(DARKGRAY);
        rlImGuiBegin();

        DrawMenuBar();
        DrawMainViewport(m_sceneView.GetRenderTexture());

        rlImGuiEnd();
        m_window.EndDrawing();
    }

    rlImGuiShutdown();

    return 0;
}

void EditorApp::DrawMenuBar()
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
                m_shouldShutdown = true;
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

void EditorApp::DrawMainViewport(raylib::RenderTexture* sceneViewRT)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::DockSpaceOverViewport(0, viewport, ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar))
    {
        ImVec2 size = ImGui::GetContentRegionAvail();
        bool resized = (size.x != m_lastSceneViewSize.x || size.y != m_lastSceneViewSize.y);
        if (resized)
        {
            m_sceneView.Resize(size.x, size.y);
            m_lastSceneViewSize = size;
        }

        rlImGuiImageRenderTextureFit(sceneViewRT, true);

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        {
            m_focusedView = EditorView::Scene;
        }
    }
    ImGui::End();
    ImGui::PopStyleVar();

    if (ImGui::Begin("Hierarchy"))
    {
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        {
            m_focusedView = EditorView::Hierarchy;
        }
    }
    ImGui::End();

    if (ImGui::Begin("Inspector"))
    {
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        {
            m_focusedView = EditorView::Inspector;
        }
    }
    ImGui::End();

    if (ImGui::Begin("Project"))
    {
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        {
            m_focusedView = EditorView::Project;
        }
    }
    ImGui::End();

    if (ImGui::Begin("Console"))
    {
        m_consoleView.Render();

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        {
            m_focusedView = EditorView::Console;
        }
    }
    ImGui::End();
}
