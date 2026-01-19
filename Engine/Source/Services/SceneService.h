#pragma once

#include "Gameplay/Scene.h"
#include "Services/Service.h"

namespace Micro
{
    class SceneService : public Service
    {
    public:
        SceneService() = default;
        ~SceneService() override = default;

        SceneService(const SceneService&) = delete;
        SceneService& operator=(const SceneService&) = delete;
        SceneService(SceneService&&) = delete;
        SceneService& operator=(SceneService&&) = delete;

        void LoadStartupScene();
        void LoadScene(const std::string& path);
        void UnloadScene();

        void SaveScene();

        Scene* GetActiveScene() const;

    private:
        std::unique_ptr<Scene> m_ActiveScene = nullptr;
    };
}  // namespace Micro
