#include "AssetsService.h"
#include "Settings/AssetsDatabaseSettings.h"
#include "Services/ServiceLocator.h"
#include "Services/SettingsService.h"

namespace Micro
{
    AssetsService::AssetsService()
    {
        auto settings = ServiceLocator::Get<SettingsService>()->LoadOrDefault<AssetsDatabaseSettings>();
        m_AssetsDatabase = settings.AssetsDB;
    }

    AssetsService::~AssetsService()
    {
        UnloadAll();

        AssetsDatabaseSettings settings;
        settings.AssetsDB = m_AssetsDatabase;
        ServiceLocator::Get<SettingsService>()->Save(settings);
    }

    void AssetsService::ScanAssets()
    {
        const std::string assetsPath = "Assets";

        if (!std::filesystem::exists(assetsPath)) std::filesystem::create_directory(assetsPath);

        for (const auto& entry : std::filesystem::recursive_directory_iterator(assetsPath))
        {
            if (!entry.is_regular_file()) continue;

            const std::string path = entry.path().string();

            if (!m_AssetsDatabase.HasAsset(path))
            {
                GUID guid;
                m_AssetsDatabase.AddAsset(guid, path);
                MICRO_LOG_INFO("New asset found: " + path);
            }
        }
    }

    AssetID AssetsService::GetAssetID(const std::string& path)
    {
        if (!m_AssetsDatabase.HasAsset(path))
        {
            return AssetID();
        }

        return AssetID(m_AssetsDatabase.GetAssetGuid(path));
    }

    std::string AssetsService::GetAssetPath(const AssetID& id)
    {
        if (!m_AssetsDatabase.HasAsset(id.ID))
        {
            return "";
        }

        return m_AssetsDatabase.GetAssetPath(id.ID);
    }

    AssetReference<MTexture2D> AssetsService::LoadTexture(const AssetID& id)
    {
        auto assetReference = AssetReference<MTexture2D>(id.ID);

        if (auto it = m_Textures.find(id.ID); it != m_Textures.end())
        {
            return assetReference;
        }

        const std::string& path = m_AssetsDatabase.GetAssetPath(id.ID);
        auto rlTexture = std::make_unique<MTexture2D>();
        rlTexture->Load(path);
        m_Textures.emplace(id.ID, std::move(rlTexture));

        return assetReference;
    }

    AssetReference<MTexture2D> AssetsService::LoadTexture(const std::string& path)
    {
        if (!m_AssetsDatabase.HasAsset(path))
        {
            GUID guid;
            m_AssetsDatabase.AddAsset(guid, path);
            return LoadTexture(AssetID(guid));
        }

        GUID guid = m_AssetsDatabase.GetAssetGuid(path);
        return LoadTexture(AssetID(guid));
    }

    MTexture2D* AssetsService::GetTexture(const GUID& id) const
    {
        if (auto it = m_Textures.find(id); it != m_Textures.end()) return it->second.get();
        return nullptr;
    }

    AssetReference<MModel> AssetsService::LoadModel(const AssetID& id)
    {
        auto assetReference = AssetReference<MModel>(id.ID);

        if (auto it = m_Models.find(id.ID); it != m_Models.end())
        {
            return assetReference;
        }

        const std::string& path = m_AssetsDatabase.GetAssetPath(id.ID);
        auto rlModel = std::make_unique<MModel>();
        rlModel->Load(path);
        m_Models.emplace(id.ID, std::move(rlModel));

        return assetReference;
    }

    AssetReference<MModel> AssetsService::LoadModel(const std::string& path)
    {
        if (!m_AssetsDatabase.HasAsset(path))
        {
            GUID guid;
            m_AssetsDatabase.AddAsset(guid, path);
            return LoadModel(AssetID(guid));
        }

        GUID guid = m_AssetsDatabase.GetAssetGuid(path);
        return LoadModel(AssetID(guid));
    }

    MModel* AssetsService::GetModel(const GUID& id) const
    {
        if (auto it = m_Models.find(id); it != m_Models.end()) return it->second.get();
        return nullptr;
    }

    void AssetsService::Unload(const AssetID& ref)
    {
        const GUID id = ref.ID;

        if (auto it = m_Textures.find(id); it != m_Textures.end())
        {
            UnloadTexture(*it->second);
            m_Textures.erase(it);
            return;
        }

        if (auto it = m_Models.find(id); it != m_Models.end())
        {
            UnloadModel(*it->second);
            m_Models.erase(it);
            return;
        }
    }

    void AssetsService::UnloadAll()
    {
        for (auto& [_, texture] : m_Textures)
            UnloadTexture(*texture);

        for (auto& [_, model] : m_Models)
            UnloadModel(*model);

        m_Textures.clear();
        m_Models.clear();
    }

    bool AssetsService::HasAsset(const std::string& path)
    {
        return m_AssetsDatabase.HasAsset(path);
    }

    bool AssetsService::IsLoaded(const AssetID& ref) const
    {
        const GUID id = ref.ID;
        return m_Textures.contains(id) || m_Models.contains(id);
    }

}  // namespace Micro
