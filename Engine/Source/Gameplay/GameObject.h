#pragma once

#include "Components/Component.h"
#include "Core/GUID.h"

namespace Micro
{
    // TODO: Replace with Events System
    using OnDestroyDelegate = std::function<void()>;

    class GameObject
    {
    public:
        GameObject(std::string name, GUID guid);
        ~GameObject() = default;

        OnDestroyDelegate OnDestroy;

        template <typename T, typename... Args>
        T* AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

            auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
            T* rawPtr = newComponent.get();
            m_Components.push_back(std::move(newComponent));

            auto component = static_cast<Component*>(rawPtr);
            component->SetOwner(this);
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
        bool HasComponent() const
        {
            return GetComponent<T>() != nullptr;
        }

        Component* GetComponent(const std::string& name) const;
        std::vector<Component*> GetAllComponents() const;

        const std::string& GetName() const { return m_Name; }
        GUID GetGUID() const { return m_Guid; }

        void Destroy(bool notify = true);

    private:
        std::vector<std::unique_ptr<Component>> m_Components;
        std::string m_Name;
        GUID m_Guid;
    };
}  // namespace Micro
