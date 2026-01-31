#pragma once

#include "Service.h"
#include "Assets/AssetsDatabase.h"
#include "Assets/AssetReference.h"

namespace Micro
{
    class AssetsService : public Service
    {
    public:
        AssetsService();
        ~AssetsService() override;

        void ScanAssets();

        AssetID GetAssetID(const std::string& path);
        std::string GetAssetPath(const AssetID& id);

        AssetReference<MTexture2D> LoadTexture(const AssetID& id);
        AssetReference<MTexture2D> LoadTexture(const std::string& path);
        MTexture2D* GetTexture(const GUID& id) const;

        AssetReference<MModel> LoadModel(const AssetID& id);
        AssetReference<MModel> LoadModel(const std::string& path);
        MModel* GetModel(const GUID& id) const;

        void Unload(const AssetID& ref);
        void UnloadAll();

        bool HasAsset(const std::string& path);
        bool IsLoaded(const AssetID& ref) const;

    private:
        AssetsDatabase m_AssetsDatabase;

        std::unordered_map<GUID, std::unique_ptr<MTexture2D>> m_Textures;
        std::unordered_map<GUID, std::unique_ptr<MModel>> m_Models;
    };
}  // namespace Micro
