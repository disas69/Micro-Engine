#include "Log.h"
#include "raylib.h"
#include <sys/time.h>

using namespace Micro;

void CustomTraceLogCallback(int logLevel, const char* text, va_list args)
{
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), text, args);
    Log::Get().AddLog(logLevel, buffer);
}

void Log::Initialize()
{
    SetTraceLogCallback(CustomTraceLogCallback);
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
    auto t = std::chrono::system_clock::to_time_t(now);

    std::tm buf = {};
#ifdef _WIN32
    localtime_s(&buf, &t);
#else
    localtime_r(&t, &buf);
#endif

    char timeStr[16];
    strftime(timeStr, sizeof(timeStr), "[%H:%M:%S]", &buf);

    m_entries.emplace_back(LogEntry{
        .Level = level,
        .Text = std::string(timeStr) + " " + text
    });

    m_scrollToBottom = true;
}

void Log::Clear()
{
    m_entries.clear();
}

void Log::ResetAutoScroll()
{
    m_scrollToBottom = false;
}