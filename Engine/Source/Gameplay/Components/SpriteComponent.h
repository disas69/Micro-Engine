#pragma once

#include "Component.h"
#include "Serialization/Reflection/Macros.h"

namespace Micro
{
    class TransformComponent;

    class SpriteComponent : public Component
    {
        MICRO_COMPONENT(SpriteComponent)

        SpriteComponent() = default;

        MTexture2D& GetSpriteTexture() { return m_spriteTexture; }
        void SetSpriteTexture(const Texture2D& texture) { m_spriteTexture = texture; }

        MRectangle& GetSourceRect() { return m_sourceRect; }
        void SetSourceRect(const MRectangle& rect) { m_sourceRect = rect; }

        MColor& GetColor() { return m_color; }
        void SetColor(const MColor& color) { m_color = color; }

    private:
        MTexture2D m_spriteTexture;
        MRectangle m_sourceRect = {0, 0, 100, 100};
        MColor m_color = MColor::White();
    };
}  // namespace Micro