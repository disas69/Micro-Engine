#pragma once

#include "Service.h"
#include "Assets/AssetsDatabase.h"
#include "Assets/AssetRef.h"

namespace Micro
{
    class AssetsService : public Service
    {
    public:
        AssetsService();
        ~AssetsService() override;

        void ScanAssets();

        AssetRef GetAssetRef(const std::string& path);
        std::string GetAssetPath(const AssetRef& ref);

        MTexture2D* LoadTexture(const AssetRef& ref);
        MTexture2D* LoadTexture(const std::string& path);

        MModel* LoadModel(const AssetRef& ref);
        MModel* LoadModel(const std::string& path);

        void Unload(const AssetRef& ref);
        void UnloadAll();

        bool HasAsset(const std::string& path);
        bool IsLoaded(const AssetRef& ref) const;

    private:
        AssetsDatabase m_AssetsDatabase;

        std::unordered_map<GUID, std::unique_ptr<MTexture2D>> m_Textures;
        std::unordered_map<GUID, std::unique_ptr<MModel>> m_Models;
    };
}  // namespace Micro
