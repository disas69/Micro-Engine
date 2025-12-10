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
    Log::Initialize();

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

    m_sceneView = SceneView(screenWidth, screenHeight);

    Log::Info("Editor App Initialized");
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

    // Scene window
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

        rlImGuiImageRenderTextureFit(renderTexture, true);
    }
    ImGui::End();
    ImGui::PopStyleVar();

    if (ImGui::Begin("Project"))
    {
    }
    ImGui::End();

    // Console window
    if (ImGui::Begin("Console"))
    {
        ImGui::BeginChild("ConsoleScrollView", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        for (auto& entry : Log::Get().GetEntries())
        {
            ImVec4 color;
            switch (entry.Level)
            {
                case LOG_INFO: color = ImVec4(1, 1, 1, 1); break;
                case LOG_WARNING: color = ImVec4(1, 1, 0, 1); break;
                case LOG_ERROR: color = ImVec4(1, 0.4f, 0.4f, 1); break;
                case LOG_FATAL: color = ImVec4(1, 0, 0, 1); break;
                default: color = ImVec4(1, 1, 1, 1); break;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(entry.Text.c_str());
            ImGui::PopStyleColor();
        }

        if (Log::Get().ShouldScrollToBottom())
        {
            ImGui::SetScrollHereY(1.0f);
        }

        Log::Get().ResetAutoScroll();

        ImGui::EndChild();
    }
    ImGui::End();

    if (ImGui::Begin("Inspector"))
    {
    }
    ImGui::End();

    if (ImGui::Begin("Hierarchy"))
    {
    }
    ImGui::End();
}
