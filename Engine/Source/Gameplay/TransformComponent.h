#pragma once

#include "Component.h"

#include <raylib-cpp.hpp>
#include <raymath.h>

namespace Micro
{
class TransformComponent : public Component
{
public:
    raylib::Vector3 Position = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 Rotation = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 Scale = {1.0f, 1.0f, 1.0f};

    TransformComponent() = default;

    raylib::Matrix GetTransformMatrix() const
    {
        raylib::Matrix matScale = MatrixScale(Scale.x, Scale.y, Scale.z);
        raylib::Matrix matRotationX = MatrixRotateX(Rotation.x * DEG2RAD);
        raylib::Matrix matRotationY = MatrixRotateY(Rotation.y * DEG2RAD);
        raylib::Matrix matRotationZ = MatrixRotateZ(Rotation.z * DEG2RAD);
        raylib::Matrix matRotation = MatrixMultiply(MatrixMultiply(matRotationX, matRotationY), matRotationZ);
        raylib::Matrix matTranslation = MatrixTranslate(Position.x, Position.y, Position.z);

        return MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
    }
};
}  // namespace Micro
