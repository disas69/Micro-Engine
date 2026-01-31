#pragma once

#include "Gameplay/Components/Component.h"
#include "Assets/AssetRef.h"

namespace Micro
{
    class ImageComponent : public Component
    {
        MICRO_COMPONENT(ImageComponent)

        explicit ImageComponent(GameObject* owner);
        ImageComponent(GameObject* owner, const AssetRef& textureRef);
        ImageComponent(GameObject* owner, const AssetRef& textureRef, MColor color);

        void OnCreate() override;
        void OnDeserialize() override;

        MTexture2D* GetTextureRaw() const { return m_Texture; }

        const AssetRef& GetTexture() const { return m_TextureRef; }
        void SetTexture(const AssetRef& textureRef);

        MRectangle& GetSourceRect() { return m_SourceRect; }
        void SetSourceRect(const MRectangle& sourceRect) { m_SourceRect = sourceRect; }

        MColor& GetColor() { return m_Color; }
        void SetColor(const MColor& color) { m_Color = color; }

    private:
        AssetRef m_TextureRef = {0};
        MRectangle m_SourceRect = {0, 0, 100, 100};
        MColor m_Color = MColor::White();

        MTexture2D* m_Texture = nullptr;
    };
}  // namespace Micro
