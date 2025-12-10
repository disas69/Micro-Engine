#pragma once

namespace Micro
{
struct LogEntry
{
    int Level;
    std::string Text;
};

class Log
{
public:
    static Log& Get()
    {
        static Log Instance;
        return Instance;
    }

    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

    std::vector<LogEntry> GetEntries() const { return m_entries; }
    bool ShouldScrollToBottom() const { return m_scrollToBottom; }

    static void Initialize();
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);
    static void Fatal(const std::string& message);

    void AddLog(int level, const std::string& text);
    void Clear();
    void ResetAutoScroll();

private:
    std::vector<LogEntry> m_entries = {};
    bool m_scrollToBottom = false;

    Log() = default;
};
}  // namespace Micro
