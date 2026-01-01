#pragma once

#include "Component.h"
#include <raylib.h>

namespace Micro
{
class GraphicComponent : public Component
{
public:
    raylib::Color Tint = WHITE;

    virtual void OnRender() override = 0;
};
}  // namespace Micro
