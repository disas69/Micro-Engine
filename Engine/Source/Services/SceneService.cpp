#include "SceneService.h"

#include "Serialization/Scene/SceneLoader.h"
#include "Serialization/Scene/SceneSaver.h"

namespace Micro
{
    void SceneService::LoadStartupScene()
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