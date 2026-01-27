#include "SceneService.h"

#include "Serialization/Scene/SceneLoader.h"
#include "Serialization/Scene/SceneSaver.h"
#include "Services/SettingsService.h"
#include "Settings/ProjectSettings.h"
#include "Services/ServiceLocator.h"

namespace Micro
{
    void SceneService::LoadStartupScene()
    {
        m_ActiveScene = std::make_unique<Scene>();

        try
        {
            auto projectSettings = ServiceLocator::Get<SettingsService>()->LoadOrDefault<ProjectSettings>();
            if (!projectSettings.Scenes.empty())
            {
                if (projectSettings.StartupSceneIndex >= projectSettings.Scenes.size())
                {
                    MICRO_LOG_WARNING("Startup scene index is out of bounds. Loading the first scene instead.");
                    projectSettings.StartupSceneIndex = 0;
                }

                SceneLoader::Load(projectSettings.Scenes[projectSettings.StartupSceneIndex], m_ActiveScene.get());
            }
        }
        catch (const std::exception& e)
        {
            MICRO_LOG_WARNING("Failed to load startup scene: " + std::string(e.what()) + ". The startup scene will be empty by default.");
        }
    }

    void SceneService::LoadScene(int index)
    {
        auto projectSettings = ServiceLocator::Get<SettingsService>()->LoadOrDefault<ProjectSettings>();

        if (!projectSettings.Scenes.empty())
        {
            if (index >= projectSettings.Scenes.size())
            {
                MICRO_LOG_ERROR("Scene index is out of bounds: " + std::to_string(index));
                return;
            }

            LoadScene(projectSettings.Scenes[index]);
        }
        else
        {
            MICRO_LOG_ERROR("No scenes available in project settings.");
        }
    }

    void SceneService::LoadScene(const std::string& path)
    {
        if (m_ActiveScene == nullptr)
        {
            m_ActiveScene = std::make_unique<Scene>();
        }
        else
        {
            m_ActiveScene->Destroy();
        }

        try
        {
            SceneLoader::Load(path, m_ActiveScene.get());
        }
        catch (const std::exception& e)
        {
            MICRO_LOG_ERROR("Failed to load scene from " + path + ": " + std::string(e.what()));
        }
    }

    void SceneService::UnloadScene()
    {
        if (m_ActiveScene != nullptr)
        {
            m_ActiveScene->Destroy();
            m_ActiveScene.reset();
        }
    }

    void SceneService::SaveScene()
    {
        SceneSaver::Save(m_ActiveScene.get(), "Startup.scene");
    }

    Scene* SceneService::GetActiveScene() const
    {
        if (m_ActiveScene != nullptr)
        {
            return m_ActiveScene.get();
        }

        MICRO_LOG_ERROR("No active scene loaded.");
        return nullptr;
    }
}  // namespace Micro