#include "ButtonComponent.h"
#include "Gameplay/Transform2dComponent.h"
#include "Gameplay/GameObject.h"

namespace Micro
{
ButtonComponent::ButtonComponent() : GraphicComponent(GraphicComponentType::GraphicTypeUI)
{
    m_text = "Button";
    m_onClick = nullptr;
}

void ButtonComponent::SetText(const std::string& text)
{
    m_text = text;
}

void ButtonComponent::SetOnClick(const std::function<void()>& onClick)
{
    m_onClick = onClick;
}

void ButtonComponent::OnRender()
{
    if (m_transform == nullptr)
    {
        m_transform = GetOwner()->GetComponent<Transform2dComponent>();
    }

    if (m_transform != nullptr)
    {
        auto position = m_transform->Position;

        if (GuiButton({position.x, position.y, Size.x, Size.y}, m_text.c_str()))
        {
            if (m_onClick != nullptr)
            {
                m_onClick();
            }
        }
    }
}
}  // namespace Micro