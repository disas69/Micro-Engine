#pragma once

#include "Component.h"

enum class GraphicComponentType : uint8_t
{
    GraphicType2D = 0,
    GraphicType3D = 1,
    GraphicTypeUI = 2
};

namespace Micro
{
class GraphicComponent : public Component
{
public:
    explicit GraphicComponent(const GraphicComponentType type) : m_graphicType(type) {}

    raylib::Color Tint = WHITE;

    virtual void OnRender() = 0;

    GraphicComponentType GetGraphicType() const { return m_graphicType; }

private:
    GraphicComponentType m_graphicType;
};
}  // namespace Micro
