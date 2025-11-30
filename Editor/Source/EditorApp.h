#pragma once

#include "raylib-cpp.hpp"
#include "imgui.h"

namespace Micro
{
class EditorApp
{
public:
    EditorApp();
    int Run();

private:
    raylib::Window m_window;
    ImVec2 m_mainViewWidth = ImVec2(650.0f, 0.0f);
    ImVec2 m_toolbarWidth = ImVec2(260.0f, 0.0f);
    ImVec2 m_contentHeight = ImVec2(0.0f, 360.0f);
};
}  // namespace Micro