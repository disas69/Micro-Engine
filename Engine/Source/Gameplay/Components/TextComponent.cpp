#include "TextComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(TextComponent,
        MICRO_FIELD(TextComponent, m_Text, FieldType::String),
        MICRO_FIELD(TextComponent, m_FontSize, FieldType::Float),
        MICRO_FIELD(TextComponent, m_Color, FieldType::Color))
    TextComponent::TextComponent(GameObject* owner) : Component(owner)
    {
    }
}  // namespace Micro