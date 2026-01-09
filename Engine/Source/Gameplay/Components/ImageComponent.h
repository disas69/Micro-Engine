#pragma once

#include "Gameplay/Components/Component.h"
#include "Serialization/Reflection/Macros.h"

namespace Micro
{
    class ImageComponent : public Component
    {
        MICRO_COMPONENT(ImageComponent)

        ImageComponent() = default;

        MTexture2D& GetTexture() { return m_texture; }
        void SetTexture(const Texture2D& texture) { m_texture = texture; }

        MRectangle& GetSourceRect() { return m_sourceRect; }
        void SetSourceRect(const MRectangle& sourceRect) { m_sourceRect = sourceRect; }

        MColor& GetColor() { return m_color; }
        void SetColor(const MColor& color) { m_color = color; }

    private:
        MTexture2D m_texture;
        MRectangle m_sourceRect = {0, 0, 100, 100};
        MColor m_color = MColor::White();
    };
}  // namespace Micro
