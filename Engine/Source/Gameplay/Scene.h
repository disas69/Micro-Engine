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
        GameObject* CreateGameObject(const std::string& name, GUID guid);

        GameObject* FindGameObjectByName(const std::string& name) const;
        GameObject* FindGameObjectByGUID(GUID guid) const;

        template<typename Component>
        GameObject* FindGameObjectByType() const
        {
            static_assert(std::is_base_of_v<Micro::Component, Component>, "Component must derive from Micro::Component");

            for (const auto& gameObject : m_GameObjects)
            {
                if (gameObject->GetComponent<Component>() != nullptr)
                {
                    return gameObject.get();
                }
            }
            return nullptr;
        }

        void Update(float deltaTime);

        void DestroyAll();

        const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const { return m_GameObjects; }

    private:
        std::vector<std::unique_ptr<GameObject>> m_GameObjects;

        void OnGameObjectDestroyed(GUID guid);
    };
}  // namespace Micro