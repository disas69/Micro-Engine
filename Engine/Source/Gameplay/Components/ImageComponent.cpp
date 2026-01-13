#include "ImageComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(ImageComponent,
        // MICRO_FIELD(ImageComponent, m_Texture, FieldType::Int),
        MICRO_FIELD(ImageComponent, m_SourceRect, FieldType::Rect),
        MICRO_FIELD(ImageComponent, m_Color, FieldType::Color))
    ImageComponent::ImageComponent(GameObject* owner) : Component(owner)
    {
        // Temp
        Image uiImg = GenImageColor(128, 128, MColor(255, 255, 255, 255));
        m_Texture = LoadTextureFromImage(uiImg);
        UnloadImage(uiImg);
    }
}  // namespace Micro