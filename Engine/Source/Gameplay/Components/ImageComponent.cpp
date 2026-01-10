#include "ImageComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(ImageComponent,
        // MICRO_FIELD(ImageComponent, m_Texture, FieldType::Int),
        MICRO_FIELD(ImageComponent, m_SourceRect, FieldType::Rect),
        MICRO_FIELD(ImageComponent, m_Color, FieldType::Color))
}