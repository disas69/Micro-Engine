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

        const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const { return m_GameObjects; }

        GameObject* CreateGameObject(const std::string& name);
        GameObject* CreateGameObject(const std::string& name, GUID guid);

        GameObject* FindGameObjectByName(const std::string& name) const;
        GameObject* FindGameObjectByGUID(GUID guid) const;

        template <typename T>
        GameObject* FindGameObjectByComponent() const
        {
            static_assert(std::is_base_of_v<Micro::Component, T>, "Component must derive from Micro::Component");

            for (const auto& gameObject : m_GameObjects)
            {
                if (gameObject->GetComponent<T>() != nullptr)
                {
                    return gameObject.get();
                }
            }
            return nullptr;
        }

        template <typename T>
        std::vector<T*> FindComponentsByType()
        {
            static_assert(std::is_base_of_v<Micro::Component, T>, "Component must derive from Micro::Component");

            std::vector<T*> components;
            for (const auto& gameObject : m_GameObjects)
            {
                T* component = gameObject->GetComponent<T>();
                if (component != nullptr)
                {
                    components.push_back(component);
                }
            }
            return components;
        }

        template <typename T>
        T* FindComponentByType()
        {
            static_assert(std::is_base_of_v<Micro::Component, T>, "Component must derive from Micro::Component");

            for (const auto& gameObject : m_GameObjects)
            {
                if (T* component = gameObject->GetComponent<T>())
                {
                    return component;
                }
            }
            return nullptr;
        }

        template <typename T>
        std::vector<GameObject*> FindGameObjectsByComponent() const
        {
            static_assert(std::is_base_of_v<Micro::Component, T>, "Component must derive from Micro::Component");

            std::vector<GameObject*> gameObjects;
            for (const auto& gameObject : m_GameObjects)
            {
                if (gameObject->GetComponent<T>() != nullptr)
                {
                    gameObjects.push_back(gameObject.get());
                }
            }
            return gameObjects;
        }

        void Update(float deltaTime);
        void LateUpdate(float deltaTime);
        void Destroy() const;

    private:
        std::vector<std::unique_ptr<GameObject>> m_GameObjects;

        void RemoveDestroyedGameObjects();
    };
}  // namespace Micro