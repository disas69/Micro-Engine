#include <imgui.h>
#include "ConsoleView.h"
#include "EditorApp.h"
#include "Core/Log.h"

using namespace Micro;

void ConsoleView::Render()
{
    LogLevelFlags* flags = Log::Get().LevelFlagsMask();
    std::vector<LogEntry> entries = Log::Get().GetEntries();

    CheckboxLogLevelFlags("Info", flags, LogLevelFlags::Info); ImGui::SameLine();
    CheckboxLogLevelFlags("Warning", flags, LogLevelFlags::Warning); ImGui::SameLine();
    CheckboxLogLevelFlags("Error", flags, LogLevelFlags::Error); ImGui::SameLine();
    CheckboxLogLevelFlags("Fatal", flags, LogLevelFlags::Fatal);

    float buttonWidth = ImGui::CalcTextSize("Clear").x+ ImGui::GetStyle().FramePadding.x * 2;
    ImGui::SameLine(ImGui::GetContentRegionAvail().x - buttonWidth);
    if (ImGui::Button("Clear"))
    {
        Log::Get().Clear();
    }

    ImGui::Separator();
    ImGui::BeginChild("ConsoleScrollView", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for (size_t i = 0; i < entries.size(); i++)
    {
        LogEntry& entry = entries[i];

        if (entry.Level == LOG_INFO && static_cast<uint32_t>(*flags & LogLevelFlags::Info) == 0) continue;
        if (entry.Level == LOG_WARNING && static_cast<uint32_t>(*flags & LogLevelFlags::Warning) == 0) continue;
        if (entry.Level == LOG_ERROR && static_cast<uint32_t>(*flags & LogLevelFlags::Error) == 0) continue;
        if (entry.Level == LOG_FATAL && static_cast<uint32_t>(*flags & LogLevelFlags::Fatal) == 0) continue;

        ImVec4 color;
        switch (entry.Level)
        {
            case LOG_INFO: color = ImVec4(1, 1, 1, 1); break;
            case LOG_WARNING: color = ImVec4(1, 1, 0, 1); break;
            case LOG_ERROR: color = ImVec4(1, 0.4f, 0.4f, 1); break;
            case LOG_FATAL: color = ImVec4(1, 0, 0, 1); break;
            default: color = ImVec4(1, 1, 1, 1); break;
        }

        ImGui::PushID(i);

        ImVec2 cursor = ImGui::GetCursorScreenPos();
        float width = ImGui::GetContentRegionAvail().x;
        float height = ImGui::GetTextLineHeightWithSpacing();

        if (i % 2 == 0)
        {
            ImGui::GetWindowDrawList()->AddRectFilled(cursor, ImVec2(cursor.x + width, cursor.y + height), IM_COL32(35, 35, 35, 255));
        }

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::Selectable(entry.Text.c_str(), false, ImGuiSelectableFlags_AllowOverlap | ImGuiSelectableFlags_SpanAllColumns);
        ImGui::PopStyleColor();

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Copy"))
            {
                ImGui::SetClipboardText(entry.Text.c_str());
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();
    }

    if (Log::Get().ShouldScrollToBottom())
    {
        ImGui::SetScrollHereY(1.0f);
        Log::Get().ResetAutoScroll();
    }

    ImGui::EndChild();
}

bool ConsoleView::CheckboxLogLevelFlags(const char* label, LogLevelFlags* flags, LogLevelFlags flag)
{
    bool value = static_cast<uint32_t>(*flags & flag) != 0;

    if (ImGui::Checkbox(label, &value))
    {
        if (value)
        {
            *flags = *flags | flag;
        }
        else
        {
            *flags = *flags & ~flag;
        }
        return true;
    }
    return false;
}