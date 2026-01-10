#pragma once

#include "Gameplay/Components/Component.h"

namespace Micro
{
    class ImageComponent : public Component
    {
        MICRO_COMPONENT(ImageComponent)

        ImageComponent() = default;

        MTexture2D& GetTexture() { return m_Texture; }
        void SetTexture(const Texture2D& texture) { m_Texture = texture; }

        MRectangle& GetSourceRect() { return m_SourceRect; }
        void SetSourceRect(const MRectangle& sourceRect) { m_SourceRect = sourceRect; }

        MColor& GetColor() { return m_Color; }
        void SetColor(const MColor& color) { m_Color = color; }

    private:
        MTexture2D m_Texture;
        MRectangle m_SourceRect = {0, 0, 100, 100};
        MColor m_Color = MColor::White();
    };
}  // namespace Micro
