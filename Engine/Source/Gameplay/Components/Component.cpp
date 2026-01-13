#include "Component.h"
#include "Gameplay/GameObject.h"

namespace Micro
{
    Component::Component(GameObject* owner)
    {
        m_GameObject = owner;
    }

    TransformComponent* Component::GetTransform() const
    {
        return GetGameObject()->GetTransform();
    }

    template <typename T>
    T* Component::GetComponent() const
    {
        return GetGameObject()->GetComponent<T>();
    }

    template <typename T>
    T* Component::GetComponentInChildren() const
    {
        return GetGameObject()->GetComponentInChildren<T>();
    }

    template <typename T>
    T* Component::GetComponentInParent() const
    {
        return GetGameObject()->GetComponentInParent<T>();
    }
}  // namespace Micro
