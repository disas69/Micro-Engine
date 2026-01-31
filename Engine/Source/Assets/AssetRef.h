#pragma once

#include "Core/GUID.h"

namespace Micro
{
    class AssetRef
    {
    public:
        AssetRef() = default;
        AssetRef(const GUID& id) : m_ID(id) {}

        const GUID& GetID() const { return m_ID; }

    private:
        GUID m_ID;
    };
}  // namespace Micro
