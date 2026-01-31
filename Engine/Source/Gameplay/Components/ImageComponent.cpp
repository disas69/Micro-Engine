#include "ImageComponent.h"
#include "Services/ServiceLocator.h"
#include "Services/AssetsService.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(ImageComponent,
        MICRO_FIELD(ImageComponent, m_TextureRef, FieldType::AssetRef),
        MICRO_FIELD(ImageComponent, m_SourceRect, FieldType::Rect),
        MICRO_FIELD(ImageComponent, m_Color, FieldType::Color))
    ImageComponent::ImageComponent(GameObject* owner) : Component(owner)
    {
    }

    void ImageComponent::SetTexture(const AssetRef& textureRef)
    {
        if (m_Texture && m_TextureRef.GetID() != textureRef.GetID())
        {
            ServiceLocator::Get<AssetsService>()->Unload(m_TextureRef);
        }

        m_TextureRef = textureRef;
        m_Texture = ServiceLocator::Get<AssetsService>()->LoadTexture(m_TextureRef);
    }
}  // namespace Micro