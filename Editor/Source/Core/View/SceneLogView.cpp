#include "SceneLogView.h"
#include "raylib.h"

namespace Micro
{
    SceneLogView::SceneLogView()
    {
        m_logEntries.reserve(m_maxVisibleSize);
    }

    void SceneLogView::AddLogEntry(const LogEntry& entry)
    {
        if (m_logEntries.size() >= m_maxVisibleSize)
        {
            m_logEntries.erase(m_logEntries.begin());
        }

        m_logEntries.push_back(entry);
    }

    void SceneLogView::Update()
    {
        auto now = std::chrono::system_clock::now();
        auto nowTimeT = std::chrono::system_clock::to_time_t(now);

        for (int i = m_logEntries.size() - 1; i >= 0; --i)
        {
            const LogEntry& entry = m_logEntries[i];
            double age = difftime(nowTimeT, entry.Timestamp);
            if (age > m_showDuration)
            {
                m_logEntries.erase(m_logEntries.begin() + i);
            }
        }
    }

    void SceneLogView::Render(ImVec2 size)
    {
        LogLevelFlags* flags = Log::Get().LevelFlagsMask();

        int yOffset = 10;
        int fontSize = 10;

        // Scale font size based on window height
        fontSize = static_cast<int>(fontSize * (size.y / 1080.0f));
        fontSize = std::max(1, std::min(fontSize, 10));

        for (const auto& entry : m_logEntries)
        {
            if (entry.Level == LOG_INFO && static_cast<uint32_t>(*flags & LogLevelFlags::Info) == 0) continue;
            if (entry.Level == LOG_WARNING && static_cast<uint32_t>(*flags & LogLevelFlags::Warning) == 0) continue;
            if (entry.Level == LOG_ERROR && static_cast<uint32_t>(*flags & LogLevelFlags::Error) == 0) continue;
            if (entry.Level == LOG_FATAL && static_cast<uint32_t>(*flags & LogLevelFlags::Fatal) == 0) continue;

            Color color = WHITE;
            switch (entry.Level)
            {
                case LOG_INFO: color = GREEN; break;
                case LOG_WARNING: color = YELLOW; break;
                case LOG_ERROR: color = RED; break;
                case LOG_FATAL: color = RED; break;
                default: break;
            }

            color.a = 200;
            DrawText(entry.Text.c_str(), 10, yOffset, fontSize, color);
            yOffset += 15;
        }
    }
}  // namespace Micro