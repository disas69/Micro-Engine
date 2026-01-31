#pragma once

#include "Gameplay/Components/Component.h"
#include "Assets/AssetReference.h"

namespace Micro
{
    class ImageComponent : public Component
    {
        MICRO_COMPONENT(ImageComponent)

        explicit ImageComponent(GameObject* owner);
        ImageComponent(GameObject* owner, const AssetID& textureID);
        ImageComponent(GameObject* owner, const AssetID& textureID, MColor color);

        void OnCreate() override;
        void OnDeserialize() override;

        MTexture2D* GetTexture() const;

        const AssetID& GetTextureID() const { return m_TextureID; }
        void SetTextureID(const AssetID& textureID);

        MRectangle& GetSourceRect() { return m_SourceRect; }
        void SetSourceRect(const MRectangle& sourceRect) { m_SourceRect = sourceRect; }

        MColor& GetColor() { return m_Color; }
        void SetColor(const MColor& color) { m_Color = color; }

    private:
        AssetID m_TextureID;
        MRectangle m_SourceRect = {0, 0, 100, 100};
        MColor m_Color = MColor::White();

        AssetReference<MTexture2D> m_Texture;
    };
}  // namespace Micro
