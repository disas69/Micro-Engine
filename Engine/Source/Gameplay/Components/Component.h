#pragma once

namespace Micro
{
    class GameObject;

    class Component
    {
    public:
        Component() = default;
        virtual ~Component() = default;

        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnDestroy() {}

        GameObject* GetOwner() const { return m_owner; }
        void SetOwner(GameObject* owner) { m_owner = owner; }

    protected:
        GameObject* m_owner = nullptr;
    };
}  // namespace Micro
