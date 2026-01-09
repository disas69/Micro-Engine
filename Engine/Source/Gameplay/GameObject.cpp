#include "GameObject.h"
#include "Serialization/Reflection/TypeRegistry.h"

namespace Micro
{
    GameObject::GameObject(std::string name, GUID guid) : m_name(std::move(name)), m_guid(guid) {}

    Component* GameObject::GetComponent(const std::string& name) const
    {
        for (const auto& component : m_components)
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
        for (const auto& component : m_components)
        {
            components.push_back(component.get());
        }
        return components;
    }
}  // namespace Micro
