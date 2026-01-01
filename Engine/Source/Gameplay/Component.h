#pragma once

namespace Micro
{
class GameObject;

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void OnInit() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnDestroy() {}

    GameObject* GetOwner() const { return m_owner; }

protected:
    GameObject* m_owner = nullptr;

    friend class GameObject;
};
}  // namespace Micro
