#pragma once

#include "Component.h"
#include "Memory/ArenaAllocator.h"

#include <vector>
#include <string>

namespace Micro
{
class GameObject
{
public:
    GameObject(ArenaAllocator& arena, std::string name);
    GameObject(ArenaAllocator& arena);
    virtual ~GameObject() = default;

    virtual void OnInit();
    virtual void OnUpdate(float deltaTime);
    virtual void OnRender();
    virtual void OnDestroy();

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        T* component = m_arena.Allocate<T>(std::forward<Args>(args)...);
        if (component != nullptr)
        {
            Component* baseComp = static_cast<Component*>(component);
            baseComp->m_owner = this;
            m_components.push_back(baseComp);
            baseComp->OnInit();
        }
        return component;
    }

    template <typename T>
    T* GetComponent() const
    {
        for (auto* component : m_components)
        {
            T* derived = dynamic_cast<T*>(component);
            if (derived != nullptr)
            {
                return derived;
            }
        }
        return nullptr;
    }

    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    bool IsActive() const { return m_isActive; }
    void SetActive(bool active) { m_isActive = active; }

protected:
    ArenaAllocator& m_arena;
    std::string m_name;
    std::vector<Component*> m_components;
    bool m_isActive = true;
};
}  // namespace Micro
