#pragma once

#include "Gameplay/Scene.h"

namespace Micro
{
    class SceneManager
    {
    public:
        static SceneManager& GetInstance()
        {
            static SceneManager instance;
            return instance;
        }

        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;
        SceneManager(SceneManager&&) = delete;
        SceneManager& operator=(SceneManager&&) = delete;

        void LoadStartupScene();
        void LoadScene(const std::string& path);
        void UnloadScene();

        void SaveScene();

        Scene* GetActiveScene() const;

    private:
        SceneManager() = default;

        std::unique_ptr<Scene> m_ActiveScene = nullptr;
    };
}  // namespace Micro
