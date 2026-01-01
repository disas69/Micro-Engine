#pragma once

#include "Component.h"

namespace Micro
{
class Transform2DComponent : public Component
{
public:
    raylib::Vector2 Position = {0.0f, 0.0f};
    float Rotation = 0.0f;
    raylib::Vector2 Scale = {1.0f, 1.0f};

    Transform2DComponent() = default;
};
}  // namespace Micro
