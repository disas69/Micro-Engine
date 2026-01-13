#pragma once

#include "Gameplay/GameObject.h"

namespace Micro
{
    class TransformComponent;

    class Component
    {
    public:
        Component() = default;
        virtual ~Component() = default;

        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnDestroy() {}

        virtual TypeDescriptor& GetTypeDescriptor() const = 0;

        GameObject* GetGameObject() const { return m_Owner; }
        void SetOwner(GameObject* owner);

        TransformComponent* GetTransform() const;

        template <typename T>
        T* GetComponent() const;

        template <typename T>
        T* GetComponentInChildren() const;

        template <typename T>
        T* GetComponentInParent() const;

    protected:
        GameObject* m_Owner = nullptr;
    };
}  // namespace Micro
