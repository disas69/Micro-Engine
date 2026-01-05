#pragma once

#include "GameObject.h"

namespace Micro
{
    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(Scene&&) = delete;

        GameObject* CreateGameObject(const std::string& name);
        void DestroyGameObject(GUID guid);

        void Update(float deltaTime);

        const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const { return m_gameObjects; }

    private:
        std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    };
}  // namespace Micro