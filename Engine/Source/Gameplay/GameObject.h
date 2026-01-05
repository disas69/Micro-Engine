#pragma once

#include "Components/Component.h"
#include "Core/GUID.h"

namespace Micro
{
    class GameObject
    {
    public:
        GameObject(std::string name, GUID guid);
        ~GameObject() = default;

        template <typename T, typename... Args>
        T* AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

            auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
            T* rawPtr = newComponent.get();
            m_components.push_back(std::move(newComponent));

            auto component = static_cast<Component*>(rawPtr);
            component->SetOwner(this);
            component->OnCreate();

            return rawPtr;
        }

        template <typename T>
        T* GetComponent() const
        {
            for (const auto& component : m_components)
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

        const std::string& GetName() const { return m_name; }
        GUID GetGUID() const { return m_guid; }

        const std::vector<std::unique_ptr<Component>>& GetComponents() const { return m_components; }

    private:
        std::string m_name;
        GUID m_guid;
        std::vector<std::unique_ptr<Component>> m_components;
    };
}  // namespace Micro
