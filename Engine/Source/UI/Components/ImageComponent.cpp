#include "ImageComponent.h"
#include "Gameplay/GameObject.h"

namespace Micro
{
ImageComponent::ImageComponent() : GraphicComponent(GraphicComponentType::GraphicTypeUI) {}

void ImageComponent::OnRender()
{
    if (m_transform == nullptr)
    {
        m_transform = GetOwner()->GetComponent<Transform2dComponent>();
    }

    if (m_transform != nullptr)
    {
        MRectangle destRect = {m_transform->Position.x, m_transform->Position.y, SourceRect.width * m_transform->Scale.x, SourceRect.height * m_transform->Scale.y};
        MVector2 origin = {0, 0};
        Texture.Draw(SourceRect, destRect, origin, m_transform->Rotation, Tint);
    }
}
}  // namespace Micro
