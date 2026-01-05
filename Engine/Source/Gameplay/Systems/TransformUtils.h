#pragma once

#include "raylib.h"

namespace Micro
{
    namespace TransformUtils
    {
        inline MMatrix BuildLocalMatrix(const MVector3& position, const MQuaternion& rotation, const MVector3& scale)
        {
            MMatrix matScale = MatrixScale(scale.x, scale.y, scale.z);
            MMatrix matRotation = QuaternionToMatrix(rotation);
            MMatrix matTranslation = MatrixTranslate(position.x, position.y, position.z);

            return MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
        }
    }  // namespace TransformUtils
}  // namespace Micro