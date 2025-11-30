#include <algorithm>
#include "raylib-cpp.hpp"
#include "imgui.h"
#include "rlImGui.h"

ImVec2 m_MainViewWidth = ImVec2(650.0f, 0.0f);
ImVec2 m_ToolbarWidth = ImVec2(260.0f, 0.0f);
ImVec2 m_ContentHeight = ImVec2(0.0f, 360.0f);

int main()
{
	int screenWidth = 1280;
	int screenHeight = 800;

	raylib::Window window(screenWidth, screenHeight, "Micro Engine");
    window.SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    window.SetTargetFPS(60);

	rlImGuiSetup(true);
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

    bool open = false;

    // Must be persistent between frames
    static float leftWidth = 300.0f;
    static float rightWidth = 250.0f;
    static float bottomHeight = 200.0f;
    float splitterSize = 5.0f;
    float minWidth = 100.0f;
    float minHeight = 100.0f;

	while (!window.ShouldClose())
	{
		window.BeginDrawing();
		window.ClearBackground(DARKGRAY);

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
                    CloseWindow();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Demo"))
                {
                    open = !open;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::Begin("MainWindow", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImVec2 size = ImGui::GetContentRegionAvail();
        float centerWidth = size.x - leftWidth - rightWidth - 2 * splitterSize;
        float topHeight = size.y - bottomHeight - splitterSize;

        // === Left Panel ===
        ImGui::BeginChild("LeftPanel", ImVec2(leftWidth, topHeight), ImGuiChildFlags_Borders);
        ImGui::Text("Main View");
        ImGui::EndChild();

        // === Vertical Splitter 1 ===
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
        ImGui::Button("##VSplitter1", ImVec2(splitterSize, topHeight));
        if (ImGui::IsItemActive()) leftWidth = std::clamp(leftWidth + ImGui::GetIO().MouseDelta.x, minWidth, size.x - rightWidth - splitterSize * 2);
        ImGui::PopStyleColor(3);

        // === Center Panel (stretch) ===
        ImGui::SameLine();
        ImGui::BeginChild("CenterPanel", ImVec2(centerWidth, topHeight), ImGuiChildFlags_Borders);
        ImGui::Text("Scene View");

        float width = ImGui::GetContentRegionAvail().x;
        float height = ImGui::GetContentRegionAvail().y;
        // ImGui::Image(ImTextureID(image.id), ImVec2(width, height));
        ImGui::EndChild();

        // === Vertical Splitter 2 ===
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
        ImGui::Button("##VSplitter2", ImVec2(splitterSize, topHeight));
        if (ImGui::IsItemActive()) rightWidth = std::clamp(rightWidth - ImGui::GetIO().MouseDelta.x, minWidth, size.x - leftWidth - splitterSize * 2);
        ImGui::PopStyleColor(3);

        // === Right Panel ===
        ImGui::SameLine();
        ImGui::BeginChild("RightPanel", ImVec2(rightWidth, topHeight), ImGuiChildFlags_Borders);
        ImGui::Text("Inspector / Details");
        ImGui::EndChild();

        // === Horizontal Splitter ===
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
        ImGui::Button("##HSplitter", ImVec2(size.x, splitterSize));
        if (ImGui::IsItemActive()) bottomHeight = std::clamp(bottomHeight - ImGui::GetIO().MouseDelta.y, minHeight, size.y - minHeight - splitterSize);
        ImGui::PopStyleColor(3);

        // === Bottom Content Panel ===
        ImGui::BeginChild("BottomPanel", ImVec2(size.x, bottomHeight), ImGuiChildFlags_Borders);
        ImGui::Text("Console / Project / Content");
        ImGui::EndChild();

	    ImGui::End();
        rlImGuiEnd();

		window.EndDrawing();
	}

    rlImGuiShutdown();

	return 0;
}