#include "GameObject.h"
#include "Gameplay/Components/TransformComponent.h"

namespace Micro
{
    GameObject::GameObject(std::string name, GUID guid) : m_Name(std::move(name)), m_Guid(guid)
    {
        m_Transform = AddComponent<TransformComponent>();
    }

    Component* GameObject::GetComponent(const std::string& name) const
    {
        for (const auto& component : m_Components)
        {
            if (component->GetTypeDescriptor().Name == name)
            {
                return component.get();
            }
        }
        return nullptr;
    }

    std::vector<Component*> GameObject::GetAllComponents() const
    {
        std::vector<Component*> components;
        components.reserve(m_Components.size());
        for (const auto& component : m_Components)
        {
            components.push_back(component.get());
        }
        return components;
    }

    void GameObject::Destroy()
    {
        if (OnDestroy != nullptr)
        {
            OnDestroy();
        }

        DestroyInternal();
    }

    void GameObject::DestroyInternal()
    {
        for (const auto& component : m_Components)
        {
            component->OnDestroy();
        }

        m_Components.clear();
    }

    template <typename T>
    T* GameObject::GetComponentInChildren() const
    {
        T* component = GetComponent<T>();
        if (component != nullptr)
        {
            return component;
        }

        for (const auto& child : GetTransform()->GetChildren())
        {
            component = child->GetGameObject()->GetComponentInChildren<T>();
            if (component != nullptr)
            {
                return component;
            }
        }

        return nullptr;
    }

    template <typename T>
    T* GameObject::GetComponentInParent() const
    {
        TransformComponent* parentTransform = GetTransform()->GetParent();
        if (parentTransform == nullptr)
        {
            return nullptr;
        }

        return parentTransform->GetGameObject()->GetComponent<T>();
    }
}  // namespace Micro
