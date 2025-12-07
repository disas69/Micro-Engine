#include "EditorApp.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "rlImGui.h"

using namespace Micro;

EditorApp::EditorApp()
{
    std::cout << "Editor App Initialized" << std::endl;

    int screenWidth = 1280;
    int screenHeight = 720;

    raylib::Window::SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    raylib::Window::Init(screenWidth, screenHeight, "Micro Engine");
    m_window.SetTargetFPS(60);

    std::string exeDir = GetApplicationDirectory();
    std::string imguiIni = exeDir + "imgui.ini";
    std::string defaultIni = exeDir + "default.ini";

    ImFileHandle iniFile = ImFileOpen(imguiIni.c_str(), "rb");
    bool isFirstLaunch = (iniFile == nullptr);
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

    m_sceneView = SceneView(screenWidth, screenHeight);
}

int EditorApp::Run()
{
    while (!raylib::Window::ShouldClose() && !m_shouldShutdown)
    {
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

void EditorApp::DrawMainViewport(raylib::RenderTexture* renderTexture)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::DockSpaceOverViewport(0, viewport, ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::Begin("Scene");
    {
        ImVec2 size = ImGui::GetWindowSize();
        bool resized = (size.x != m_lastSceneViewSize.x || size.y != m_lastSceneViewSize.y);
        if (resized)
        {
            m_sceneView.Resize(size.x, size.y);
            m_lastSceneViewSize = size;
        }

        rlImGuiImageRenderTextureFit(renderTexture, true);
    }
    ImGui::End();

    ImGui::Begin("Project");
    {
    }
    ImGui::End();

    ImGui::Begin("Console");
    {
    }
    ImGui::End();

    ImGui::Begin("Inspector");
    {
    }
    ImGui::End();

    ImGui::Begin("Hierarchy");
    {
    }
    ImGui::End();
}
