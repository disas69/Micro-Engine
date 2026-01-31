#pragma once

#include "Core/GUID.h"

namespace Micro
{
    struct AssetID
    {
        GUID ID;

        AssetID() : ID(0) {}
        explicit AssetID(const GUID& id) : ID(id) {}

        bool IsValid() const { return ID.IsValid(); }
    };
}  // namespace Micro
