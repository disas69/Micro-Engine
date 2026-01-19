#pragma once

#include "Components/Component.h"
#include "Core/GUID.h"

namespace Micro
{
    class TransformComponent;
    class Scene;

    class GameObject
    {
        friend class Scene;

    public:
        static GameObject* Create(const std::string& name);

        GameObject(Scene* scene, std::string name, GUID guid);
        ~GameObject() = default;

        template <typename T, typename... Args>
        T* AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

            auto newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
            T* rawPtr = newComponent.get();
            m_Components.push_back(std::move(newComponent));

            auto component = static_cast<Component*>(rawPtr);
            component->OnCreate();

            return rawPtr;
        }

        template <typename T>
        T* GetComponent() const
        {
            for (const auto& component : m_Components)
            {
                if (T* castedComponent = dynamic_cast<T*>(component.get()))
                {
                    return castedComponent;
                }
            }
            return nullptr;
        }

        template <typename T>
        T* GetComponentInChildren() const;

        template <typename T>
        T* GetComponentInParent() const;

        template <typename T>
        bool HasComponent() const
        {
            return GetComponent<T>() != nullptr;
        }

        Component* GetComponent(const std::string& name) const;
        std::vector<Component*> GetAllComponents() const;

        TransformComponent* GetTransform() const { return m_Transform; }

        Scene* GetScene() const { return m_Scene; }
        const std::string& GetName() const { return m_Name; }
        GUID GetGUID() const { return m_Guid; }

        bool IsActive() const { return m_IsActive && !m_IsDestroyed; }
        void SetActive(bool isActive) { m_IsActive = isActive; }

        void Destroy();
        bool IsDestroyed() const { return m_IsDestroyed; }

    private:
        std::vector<std::unique_ptr<Component>> m_Components;
        std::string m_Name;
        GUID m_Guid;
        TransformComponent* m_Transform = nullptr;
        Scene* m_Scene = nullptr;
        bool m_IsActive = true;
        bool m_IsDestroyed = false;

        void RemoveDestroyedComponents();
    };
}  // namespace Micro
