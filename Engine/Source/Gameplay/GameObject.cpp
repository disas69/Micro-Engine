#include "GameObject.h"

namespace Micro
{
GameObject::GameObject(ArenaAllocator& arena, std::string name)
    : m_arena(arena), m_name(std::move(name))
{
}

GameObject::GameObject(ArenaAllocator& arena)
    : m_arena(arena), m_name("GameObject")
{
}

void GameObject::OnInit()
{
    for (auto* component : m_components)
    {
        component->OnInit();
    }
}

void GameObject::OnUpdate(float deltaTime)
{
    if (!m_isActive)
    {
        return;
    }

    for (auto* component : m_components)
    {
        component->OnUpdate(deltaTime);
    }
}

void GameObject::OnRender()
{
    if (!m_isActive)
    {
        return;
    }

    for (auto* component : m_components)
    {
        component->OnRender();
    }
}

void GameObject::OnDestroy()
{
    for (auto* component : m_components)
    {
        component->OnDestroy();
    }
}
} // namespace Micro
