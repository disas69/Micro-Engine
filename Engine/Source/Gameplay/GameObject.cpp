#include "GameObject.h"
#include "Serialization/Reflection/TypeRegistry.h"

namespace Micro
{
    GameObject::GameObject(std::string name, GUID guid) : m_Name(std::move(name)), m_Guid(guid) {}

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
        for (const auto& component : m_Components)
        {
            components.push_back(component.get());
        }
        return components;
    }

    void GameObject::Destroy(bool notify)
    {
        if (notify && OnDestroy != nullptr)
        {
            OnDestroy();
        }

        for (const auto& component : m_Components)
        {
            component->OnDestroy();
        }

        m_Components.clear();
    }
}  // namespace Micro
