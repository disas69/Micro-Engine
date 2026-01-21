#pragma once

namespace Micro
{
    struct Settings
    {
        virtual ~Settings() = default;
        virtual std::string GetFileName() = 0;
    };
}  // namespace Micro