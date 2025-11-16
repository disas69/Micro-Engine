#pragma once

#include "EngineConfig.h"

namespace Micro
{
class Engine final
{
public:
    Engine();

    static constexpr std::string_view version()
    {
        return ENGINE_VERSION_STRING;
    }
};
}