#pragma once

namespace Micro
{
    #if defined(_DEBUG) || !defined(NDEBUG)

    #define MICRO_LOG_INFO(msg) Micro::Log::Info(msg)
    #define MICRO_LOG_WARNING(msg) Micro::Log::Warning(msg)
    #define MICRO_LOG_ERROR(msg) Micro::Log::Error(msg)
    #define MICRO_LOG_FATAL(msg) Micro::Log::Fatal(msg)

    #else

    #define MICRO_LOG_INFO(msg) ((void)0)
    #define MICRO_LOG_WARNING(msg) ((void)0)
    #define MICRO_LOG_ERROR(msg) ((void)0)
    #define MICRO_LOG_FATAL(msg) ((void)0)

    #endif

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

        std::vector<LogEntry> GetEntries() const { return m_Entries; }
        bool ShouldScrollToBottom() const { return m_ScrollToBottom; }

        static void Initialize();
        static void Info(const std::string& message);
        static void Warning(const std::string& message);
        static void Error(const std::string& message);
        static void Fatal(const std::string& message);

        void AddLog(int level, const std::string& text);
        void Clear();
        void ResetAutoScroll();

        void SetLogCallback(const std::function<void(const LogEntry&)>& callback) { m_LogCallback = callback; }
        LogLevelFlags* LevelFlagsMask() { return &m_LevelMask; }

    private:
        std::vector<LogEntry> m_Entries = {};
        std::function<void(const LogEntry&)> m_LogCallback = nullptr;
        LogLevelFlags m_LevelMask = LogLevelFlags::All;
        bool m_ScrollToBottom = false;

        Log() = default;
    };
}  // namespace Micro
