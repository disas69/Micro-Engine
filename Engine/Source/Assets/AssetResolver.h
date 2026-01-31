#pragma once

#include "Core/GUID.h"

namespace Micro
{
    template <typename T>
    struct AssetResolver
    {
        static T* Resolve(const GUID& id);
    };
}  // namespace Micro
