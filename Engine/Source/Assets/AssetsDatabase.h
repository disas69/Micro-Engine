#pragma once

#include "Core/GUID.h"

namespace Micro
{
    class AssetsDatabase
    {
    public:
        AssetsDatabase() = default;

        void AddAsset(const GUID& id, const std::string& path);
        const std::string& GetAssetPath(const GUID& id) const;
        GUID GetAssetGuid(const std::string& path) const;
        bool HasAsset(const GUID& id) const;
        bool HasAsset(const std::string& path) const;

        const std::unordered_map<GUID, std::string>& GetAssets() const { return m_Assets; }

    private:
        std::unordered_map<GUID, std::string> m_Assets;
        std::unordered_map<std::string, GUID> m_PathToGuid;
    };
}  // namespace Micro
