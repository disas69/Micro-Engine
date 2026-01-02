#pragma once

#include "Gameplay/GraphicComponent.h"

namespace Micro
{
class Transform2DComponent;

class TextComponent : public GraphicComponent
{
public:
    TextComponent();

    void OnRender() override;

    std::string Text;
    float FontSize = 20.0f;
    raylib::Color Color;

private:
    Transform2DComponent* m_transform = nullptr;
};
}  // namespace Micro
