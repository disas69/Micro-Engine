#include "AssetsDatabase.h"

namespace Micro
{
    void AssetsDatabase::AddAsset(const GUID& id, const std::string& path)
    {
        m_Assets[id] = path;
        m_PathToGuid[path] = id;
    }

    const std::string& AssetsDatabase::GetAssetPath(const GUID& id) const
    {
        return m_Assets.at(id);
    }

    GUID AssetsDatabase::GetAssetGuid(const std::string& path) const
    {
        return m_PathToGuid.at(path);
    }

    bool AssetsDatabase::HasAsset(const GUID& id) const
    {
        return m_Assets.contains(id);
    }

    bool AssetsDatabase::HasAsset(const std::string& path) const
    {
        return m_PathToGuid.contains(path);
    }
}  // namespace Micro
