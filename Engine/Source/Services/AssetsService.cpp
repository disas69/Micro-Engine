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

    MTexture2D* AssetsService::LoadTexture(const AssetRef& ref)
    {
        if (auto it = m_Textures.find(ref.GetID()); it != m_Textures.end())
        {
            return it->second.get();
        }

        const std::string& path = m_AssetsDatabase.GetAssetPath(ref.GetID());

        MTexture2D* rlTexture = LoadTexture(path);
        auto texture = std::unique_ptr<MTexture2D>(rlTexture);

        MTexture2D* raw = texture.get();
        m_Textures.emplace(ref.GetID(), std::move(texture));

        return raw;
    }

    MTexture2D* AssetsService::LoadTexture(const std::string& path)
    {
        if (!m_AssetsDatabase.HasAsset(path))
        {
            GUID guid;
            m_AssetsDatabase.AddAsset(guid, path);
            return LoadTexture(AssetRef(guid));
        }

        GUID guid = m_AssetsDatabase.GetAssetGuid(path);
        return LoadTexture(AssetRef(guid));
    }

    MModel* AssetsService::LoadModel(const AssetRef& ref)
    {
        if (auto it = m_Models.find(ref.GetID()); it != m_Models.end())
        {
            return it->second.get();
        }

        const std::string& path = m_AssetsDatabase.GetAssetPath(ref.GetID());

        MModel* rlModel = LoadModel(path);
        auto model = std::unique_ptr<MModel>(rlModel);

        MModel* raw = model.get();
        m_Models.emplace(ref.GetID(), std::move(model));

        return raw;
    }

    MModel* AssetsService::LoadModel(const std::string& path)
    {
        if (!m_AssetsDatabase.HasAsset(path))
        {
            GUID guid;
            m_AssetsDatabase.AddAsset(guid, path);
            return LoadModel(AssetRef(guid));
        }

        GUID guid = m_AssetsDatabase.GetAssetGuid(path);
        return LoadModel(AssetRef(guid));
    }

    void AssetsService::Unload(const AssetRef& ref)
    {
        const GUID id = ref.GetID();

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

    bool AssetsService::IsLoaded(const AssetRef& ref) const
    {
        const GUID id = ref.GetID();
        return m_Textures.contains(id) || m_Models.contains(id);
    }

}  // namespace Micro
