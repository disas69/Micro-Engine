#include "GameObject.h"
#include "GraphicComponent.h"

namespace Micro
{
GameObject::GameObject(ArenaAllocator& arena, std::string name) : m_arena(arena), m_name(std::move(name)) {}

GameObject::GameObject(ArenaAllocator& arena) : m_arena(arena), m_name("GameObject") {}

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
        if (component->IsActive())
        {
            component->OnUpdate(deltaTime);
        }
    }
}

void GameObject::OnRender3D()
{
    if (!m_isActive)
    {
        return;
    }

    for (auto* component : m_components)
    {
        if (component->IsActive())
        {
            auto graphicComponent = dynamic_cast<GraphicComponent*>(component);
            if (graphicComponent != nullptr && graphicComponent->GetGraphicType() == GraphicComponentType::GraphicType3D)
            {
                graphicComponent->OnRender();
            }
        }
    }
}

void GameObject::OnRender2D()
{
    if (!m_isActive)
    {
        return;
    }

    for (auto* component : m_components)
    {
        if (component->IsActive())
        {
            auto graphicComponent = dynamic_cast<GraphicComponent*>(component);
            if (graphicComponent != nullptr && graphicComponent->GetGraphicType() == GraphicComponentType::GraphicType2D)
            {
                graphicComponent->OnRender();
            }
        }
    }
}

void GameObject::OnRenderUI()
{
    if (!m_isActive)
    {
        return;
    }

    for (auto* component : m_components)
    {
        if (component->IsActive())
        {
            auto graphicComponent = dynamic_cast<GraphicComponent*>(component);
            if (graphicComponent != nullptr && graphicComponent->GetGraphicType() == GraphicComponentType::GraphicTypeUI)
            {
                graphicComponent->OnRender();
            }
        }
    }
}

void GameObject::OnDestroy()
{
    for (auto* component : m_components)
    {
        component->OnDestroy();
    }
}

void GameObject::SetActive(bool active)
{
    if (m_isActive == active)
    {
        return;
    }

    m_isActive = active;

    if (m_isActive)
    {
        OnEnable();
    }
    else
    {
        OnDisable();
    }
}
}  // namespace Micro
