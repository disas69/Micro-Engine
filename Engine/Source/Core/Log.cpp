#include "Log.h"
#include "raylib.h"

namespace Micro
{
    void ProcessTraceLog(int logLevel, const char* text, va_list args)
    {
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), text, args);
        Log::Get().AddLog(logLevel, buffer);
    }

    void Log::Initialize()
    {
        SetTraceLogCallback(ProcessTraceLog);
    }

    void Log::Info(const std::string& message)
    {
        TraceLog(LOG_INFO, message.c_str());
    }

    void Log::Warning(const std::string& message)
    {
        TraceLog(LOG_WARNING, message.c_str());
    }

    void Log::Error(const std::string& message)
    {
        TraceLog(LOG_ERROR, message.c_str());
    }

    void Log::Fatal(const std::string& message)
    {
        TraceLog(LOG_FATAL, message.c_str());
    }

    void Log::AddLog(int level, const std::string& text)
    {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::system_clock::to_time_t(now);

        std::tm buf = {};
#ifdef _WIN32
        localtime_s(&buf, &timestamp);
#else
        localtime_r(&timestamp, &buf);
#endif

        char timeStr[16];
        strftime(timeStr, sizeof(timeStr), "[%H:%M:%S]", &buf);

        LogEntry entry = LogEntry{.Level = static_cast<uint32_t>(level), .Text = std::string(timeStr) + " " + text, .Timestamp = timestamp};

        if (m_LogCallback != nullptr)
        {
            m_LogCallback(entry);
        }

        m_Entries.emplace_back(std::move(entry));

        m_ScrollToBottom = true;
    }

    void Log::Clear()
    {
        m_Entries.clear();
    }

    void Log::ResetAutoScroll()
    {
        m_ScrollToBottom = false;
    }
}  // namespace Micro
