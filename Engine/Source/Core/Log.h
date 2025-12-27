#pragma once

namespace Micro
{
enum class LogLevelFlags : uint32_t
{
    None = 0,
    Info = 1 << 0,
    Warning = 1 << 1,
    Error = 1 << 2,
    Fatal = 1 << 3,
    All = Info | Warning | Error | Fatal
};

inline LogLevelFlags operator|(LogLevelFlags a, LogLevelFlags b)
{
    return static_cast<LogLevelFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline LogLevelFlags operator&(LogLevelFlags a, LogLevelFlags b)
{
    return static_cast<LogLevelFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

inline LogLevelFlags operator~(LogLevelFlags a)
{
    return static_cast<LogLevelFlags>(~static_cast<uint32_t>(a));
}

struct LogEntry
{
    uint32_t Level;
    std::string Text;
    time_t Timestamp;
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

    void SetLogCallback(const std::function<void(const LogEntry&)>& callback) { m_logCallback = callback; }
    LogLevelFlags* LevelFlagsMask() { return &m_levelMask; }

private:
    std::vector<LogEntry> m_entries = {};
    std::function<void(const LogEntry&)> m_logCallback = nullptr;
    LogLevelFlags m_levelMask = LogLevelFlags::All;
    bool m_scrollToBottom = false;

    Log() = default;
};
}  // namespace Micro
