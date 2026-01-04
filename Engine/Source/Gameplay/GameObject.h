#pragma once

#include "Components/Component.h"

namespace Micro
{
class GameObject
{
public:
    explicit GameObject(std::string name);
    GameObject();
    virtual ~GameObject() = default;

    virtual void OnInit();
    virtual void OnUpdate(float deltaTime);
    virtual void OnRender3D();
    virtual void OnRender2D();
    virtual void OnRenderUI();
    virtual void OnDestroy();

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = component.get();

        Component* baseComp = static_cast<Component*>(rawPtr);
        baseComp->m_owner = this;

        m_components.push_back(std::move(component));
        baseComp->OnInit();

        return rawPtr;
    }

    template <typename T>
    T* GetComponent() const
    {
        for (const auto& component : m_components)
        {
            T* derived = dynamic_cast<T*>(component.get());
            if (derived != nullptr)
            {
                return derived;
            }
        }
        return nullptr;
    }

    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    void Enable() { SetActive(true); }
    void Disable() { SetActive(false); }

    bool IsActive() const { return m_isActive; }
    void SetActive(bool active);

    virtual void OnEnable() {}
    virtual void OnDisable() {}

protected:
    std::string m_name;
    std::vector<std::unique_ptr<Component>> m_components;
    bool m_isActive = true;
};
}  // namespace Micro
