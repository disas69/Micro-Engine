#pragma once

#include "Core/Log.h"

namespace Micro
{
class SceneLogView
{
public:
    SceneLogView();
    void AddLogEntry(const LogEntry& entry);
    void Update();
    void Render();

private:
    std::vector<LogEntry> m_logEntries;
    float m_showDuration = 3.0f;
    size_t m_maxVisibleSize = 100;
};
}  // namespace Micro
