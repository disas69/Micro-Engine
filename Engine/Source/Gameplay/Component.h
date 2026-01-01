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
    virtual void OnDestroy() {}
    virtual void OnEnable() {}
    virtual void OnDisable() {}

    void Enable() { SetActive(true); }
    void Disable() { SetActive(false); }

    bool IsActive() const { return m_isActive; }
    void SetActive(bool active);

    GameObject* GetOwner() const { return m_owner; }

protected:
    GameObject* m_owner = nullptr;
    bool m_isActive = true;

    friend class GameObject;
};
}  // namespace Micro
