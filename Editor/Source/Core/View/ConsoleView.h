#pragma once

#include "Core/Log.h"

namespace Micro
{
    class ConsoleView
    {
    public:
        ConsoleView() = default;
        ~ConsoleView() = default;

        ConsoleView(const ConsoleView&) = delete;
        ConsoleView& operator=(const ConsoleView&) = delete;
        ConsoleView(ConsoleView&& other) = delete;
        ConsoleView& operator=(ConsoleView&& other) = delete;

        void Render();

    private:
        static bool CheckboxLogLevelFlags(const char* label, LogLevelFlags* flags, LogLevelFlags flag);
    };
}  // namespace Micro
