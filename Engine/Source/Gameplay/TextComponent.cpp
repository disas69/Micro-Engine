#include "TextComponent.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Transform2DComponent.h"

namespace Micro
{
TextComponent::TextComponent() : GraphicComponent(GraphicComponentType::GraphicTypeUI)
{
    Color = raylib::Color(0, 0, 0, 255);
}

void TextComponent::OnRender()
{
    if (m_transform == nullptr)
    {
        m_transform = GetOwner()->GetComponent<Transform2DComponent>();
    }

    if (m_transform != nullptr)
    {
        raylib::DrawText(Text, m_transform->Position.x, m_transform->Position.y, FontSize, Color);
    }
}
}  // namespace Micro
