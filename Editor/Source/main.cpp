#include "EditorApp.h"
#include "raylib-cpp.hpp"
#include "imgui.h"
#include "rlImGui.h"

int main()
{
    Micro::EditorApp editor;

	int screenWidth = 1280;
	int screenHeight = 800;

    raylib::Window window(screenWidth, screenHeight, "raylib-Extras [ImGui] example - simple ImGui Demo");
	window.SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	window.SetTargetFPS(144);

    rlImGuiSetup(true);

	// Main game loop
	while (!window.ShouldClose())    // Detect window close button or ESC key
	{
		window.BeginDrawing();
		window.ClearBackground(DARKGRAY);

		// start ImGui Conent
		rlImGuiBegin();

		bool open = true;
		ImGui::ShowDemoWindow(&open);

		open = true;
		if (ImGui::Begin("Test Window", &open))
		{
			ImGui::TextUnformatted(ICON_FA_JEDI);
		}
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();

		window.EndDrawing();
	}

    rlImGuiShutdown();

    return 0;
}