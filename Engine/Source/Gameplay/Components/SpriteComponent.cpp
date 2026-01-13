#include "SpriteComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(SpriteComponent,
        // MICRO_FIELD(SpriteComponent, m_SpriteTexture, FieldType::Int),
        MICRO_FIELD(SpriteComponent, m_SourceRect, FieldType::Rect),
        MICRO_FIELD(SpriteComponent, m_Color, FieldType::Color))
    SpriteComponent::SpriteComponent(GameObject* owner) : Component(owner)
    {

    }
}  // namespace Micro