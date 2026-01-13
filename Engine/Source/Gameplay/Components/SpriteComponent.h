#pragma once

#include "Component.h"

namespace Micro
{
    class TransformComponent;

    class SpriteComponent : public Component
    {
        MICRO_COMPONENT(SpriteComponent)

        explicit SpriteComponent(GameObject* owner);

        MTexture2D& GetSpriteTexture() { return m_SpriteTexture; }
        void SetSpriteTexture(const Texture2D& texture) { m_SpriteTexture = texture; }

        MRectangle& GetSourceRect() { return m_SourceRect; }
        void SetSourceRect(const MRectangle& rect) { m_SourceRect = rect; }

        MColor& GetColor() { return m_Color; }
        void SetColor(const MColor& color) { m_Color = color; }

    private:
        MTexture2D m_SpriteTexture;
        MRectangle m_SourceRect = {0, 0, 100, 100};
        MColor m_Color = MColor::White();
    };
}  // namespace Micro