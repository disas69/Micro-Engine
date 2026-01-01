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

    GraphicComponentType GetGraphicType() const { return m_graphicType; }
    virtual void OnRender() = 0;

    raylib::Color Tint = WHITE;

private:
    GraphicComponentType m_graphicType;
};
}  // namespace Micro
