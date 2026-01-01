#pragma once

#include "GraphicComponent.h"
#include "Transform2DComponent.h"
#include "GameObject.h"

namespace Micro
{
class SpriteComponent : public GraphicComponent
{
public:
    SpriteComponent() : GraphicComponent(GraphicComponentType::GraphicType2D) {}

    raylib::Texture2D SpriteTexture = {};
    raylib::Rectangle SourceRect = raylib::Rectangle{0, 0, 0, 0};

    void OnRender() override
    {
        Transform2DComponent* transform = m_owner->GetComponent<Transform2DComponent>();
        if (transform != nullptr)
        {
            Vector2 origin = {(SourceRect.width * transform->Scale.x) / 2.0f, (SourceRect.height * transform->Scale.y) / 2.0f};
            Rectangle destRect = {transform->Position.x, transform->Position.y, SourceRect.width * transform->Scale.x, SourceRect.height * transform->Scale.y};

            if (SpriteTexture.id != 0)
            {
                DrawTexturePro(SpriteTexture, SourceRect, destRect, origin, transform->Rotation, Tint);
            }
            else
            {
                DrawRectanglePro(destRect, origin, transform->Rotation, Tint);
            }
        }
    }
};
}  // namespace Micro
