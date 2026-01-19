#pragma once

#include "Gameplay/GameObject.h"

namespace Micro
{
    class TransformComponent;
    class Scene;

    class Component
    {
    public:
        explicit Component(GameObject* owner);
        virtual ~Component() = default;

        virtual void OnCreate() {}
        virtual void OnEnable() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnLateUpdate(float deltaTime) {}
        virtual void OnDisable() {}
        virtual void OnDestroy() {}

        virtual TypeDescriptor& GetTypeDescriptor() const = 0;
        GameObject* GetGameObject() const { return m_GameObject; }
        TransformComponent* GetTransform() const;
        Scene* GetScene() const;

        template <typename T>
        T* GetComponent() const;

        template <typename T>
        T* GetComponentInChildren() const;

        template <typename T>
        T* GetComponentInParent() const;

        void SetEnabled(bool isEnabled);
        bool IsEnabled() const { return m_IsEnabled && !m_IsDestroyed; }

        void Destroy();
        bool IsDestroyed() const { return m_IsDestroyed; }

    protected:
        GameObject* m_GameObject = nullptr;
        bool m_IsEnabled = true;
        bool m_IsDestroyed = false;
    };
}  // namespace Micro
