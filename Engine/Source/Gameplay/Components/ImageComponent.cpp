#include "ImageComponent.h"
#include "Services/ServiceLocator.h"
#include "Services/AssetsService.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(ImageComponent,
        MICRO_FIELD(ImageComponent, m_TextureID, FieldType::AssetID),
        MICRO_FIELD(ImageComponent, m_SourceRect, FieldType::Rect),
        MICRO_FIELD(ImageComponent, m_Color, FieldType::Color))
    ImageComponent::ImageComponent(GameObject* owner) : Component(owner)
    {
    }

    ImageComponent::ImageComponent(GameObject* owner, const AssetID& textureID) : Component(owner), m_TextureID(textureID)
    {
    }

    ImageComponent::ImageComponent(GameObject* owner, const AssetID& textureID, MColor color) : Component(owner), m_TextureID(textureID), m_Color(color)
    {
    }

    void ImageComponent::OnCreate()
    {
        Component::OnCreate();

        if (m_TextureID.IsValid())
        {
            m_Texture = ServiceLocator::Get<AssetsService>()->LoadTexture(m_TextureID);
        }
    }

    void ImageComponent::OnDeserialize()
    {
        Component::OnDeserialize();

        if (m_TextureID.IsValid())
        {
            m_Texture = ServiceLocator::Get<AssetsService>()->LoadTexture(m_TextureID);
        }
    }

    MTexture2D* ImageComponent::GetTexture() const
    {
        if (m_Texture.IsValid())
        {
            return m_Texture.Get();
        }

        return nullptr;
    }

    void ImageComponent::SetTextureID(const AssetID& textureID)
    {
        if (textureID.IsValid() && m_Texture && m_TextureID.ID != textureID.ID)
        {
            ServiceLocator::Get<AssetsService>()->Unload(m_TextureID);
        }

        m_TextureID = textureID;
        m_Texture = ServiceLocator::Get<AssetsService>()->LoadTexture(m_TextureID);
    }
}  // namespace Micro