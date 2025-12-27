#pragma once

#include "Core/Log.h"

namespace Micro
{
class ConsoleView
{
public:
    void Render();

private:
    static bool CheckboxLogLevelFlags(const char* label, LogLevelFlags* flags, LogLevelFlags flag);
};
}  // namespace Micro
