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

    void Component::SetEnabled(bool isEnabled)
    {
        if (m_IsEnabled != isEnabled)
        {
            m_IsEnabled = isEnabled;

            if (m_IsEnabled)
            {
                OnEnable();
            }
            else
            {
                OnDisable();
            }
        }
    }

    void Component::Destroy()
    {
        m_IsDestroyed = true;
        OnDestroy();
    }
}  // namespace Micro
