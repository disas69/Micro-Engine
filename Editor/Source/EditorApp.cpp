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

    m_window.SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    m_window.Init(screenWidth, screenHeight, "Micro Engine");
    m_window.SetTargetFPS(60);

    std::string exeDir = GetApplicationDirectory();
    std::string imguiIni = exeDir + "imgui.ini";
    std::string defaultIni = exeDir + "default.ini";

    ImFileHandle iniFile = ImFileOpen(imguiIni.c_str(), "rb");
    bool isFirstLaunch = (iniFile == nullptr);
    if (iniFile) ImFileClose(iniFile);

    rlImGuiSetup(true);

    ImGui::GetIO().IniFilename = strdup(imguiIni.c_str());
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().FontGlobalScale = 1.2f;

    if (isFirstLaunch)
    {
        ImGui::LoadIniSettingsFromDisk(defaultIni.c_str());
    }
}

int EditorApp::Run()
{
    while (!m_window.ShouldClose())
    {
        m_window.BeginDrawing();
        m_window.ClearBackground(DARKGRAY);

        rlImGuiBegin();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open"))
                {
                }

                if (ImGui::MenuItem("Quit"))
                {
                    m_window.Close();
                    return EXIT_SUCCESS;
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

        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::Begin("Scene");
        ImGui::End();

        ImGui::Begin("Project");
        ImGui::End();

        ImGui::Begin("Console");
        ImGui::End();

        ImGui::Begin("Inspector");
        ImGui::End();

        ImGui::Begin("Hierarchy");
        ImGui::End();

        rlImGuiEnd();
        m_window.EndDrawing();
    }

    rlImGuiShutdown();

    return 0;
}
