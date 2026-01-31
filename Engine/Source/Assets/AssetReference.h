#pragma once

#include "AssetID.h"
#include "Core/GUID.h"

namespace Micro
{
    template <typename T>
    class AssetReference
    {
    public:
        AssetReference() = default;
        explicit AssetReference(const GUID& id) : m_ID(id) {}
        explicit AssetReference(const AssetID& id) : m_ID(id.ID) {}

        AssetID ToAssetID() const { return AssetID(m_ID); }

        bool IsValid() const { return m_ID.IsValid(); }
        const GUID& GetID() const { return m_ID; }

        T* Get() const;  // defined elsewhere

        T* operator->() const { return Get(); }
        T& operator*() const { return *Get(); }
        explicit operator bool() const { return Get() != nullptr; }

    private:
        GUID m_ID;
    };
}  // namespace Micro

#include "AssetResolver.h"

namespace Micro
{
    template <typename T>
    inline T* AssetReference<T>::Get() const
    {
        if (!IsValid()) return nullptr;

        return AssetResolver<T>::Resolve(m_ID);
    }
}  // namespace Micro
