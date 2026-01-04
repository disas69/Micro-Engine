#pragma once

#include "Gameplay/Components/GraphicComponent.h"
#include "Gameplay/Components/Transform2dComponent.h"

namespace Micro
{
class ImageComponent : public GraphicComponent
{
public:
    ImageComponent();

    void OnRender() override;

    MTexture2D Texture;
    MRectangle SourceRect = {0, 0, 100, 100};

private:
    Transform2dComponent* m_transform = nullptr;
};
}  // namespace Micro
