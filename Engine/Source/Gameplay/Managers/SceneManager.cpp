#include "SceneManager.h"

#include "Serialization/Scene/SceneLoader.h"
#include "Serialization/Scene/SceneSaver.h"

namespace Micro
{
    void SceneManager::LoadStartupScene()
    {
        m_ActiveScene = std::make_unique<Scene>();

        try
        {
            SceneLoader::Load("Startup.scene", m_ActiveScene.get());
        }
        catch (const std::exception& e)
        {
            MICRO_LOG_WARNING("Failed to load startup scene: " + std::string(e.what()) + ". The startup scene will be empty by default.");
        }
    }

    void SceneManager::LoadScene(const std::string& path)
    {
        if (m_ActiveScene == nullptr)
        {
            m_ActiveScene = std::make_unique<Scene>();
        }
        else
        {
            m_ActiveScene->Clear();
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

    void SceneManager::UnloadScene()
    {
        if (m_ActiveScene != nullptr)
        {
            m_ActiveScene->Clear();
            m_ActiveScene.reset();
        }
    }

    void SceneManager::SaveScene()
    {
        SceneSaver::Save(m_ActiveScene.get(), "Startup.scene");
    }

    Scene* SceneManager::GetActiveScene() const
    {
        if (m_ActiveScene != nullptr)
        {
            return m_ActiveScene.get();
        }

        MICRO_LOG_ERROR("No active scene loaded.");
        return nullptr;
    }
}  // namespace Micro