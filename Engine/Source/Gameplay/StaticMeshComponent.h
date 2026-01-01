#pragma once

#include "GraphicComponent.h"
#include "Transform2DComponent.h"
#include "GameObject.h"
#include <raylib.h>
#include <raymath.h>

namespace Micro
{
class StaticMeshComponent : public GraphicComponent
{
public:
    raylib::Mesh ObjectMesh = {};
    raylib::Material ObjectMaterial = {};

    StaticMeshComponent() { ObjectMaterial = LoadMaterialDefault(); }

    void OnRender() override
    {
        Transform2DComponent* transform = m_owner->GetComponent<Transform2DComponent>();
        if (transform && ObjectMesh.vertexCount > 0)
        {
            Matrix matScale = MatrixScale(transform->Scale.x, transform->Scale.y, 1.0f);
            Matrix matRotation = MatrixRotateZ(transform->Rotation * DEG2RAD);
            Matrix matTranslation = MatrixTranslate(transform->Position.x, transform->Position.y, 0.0f);

            Matrix transformMatrix = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);

            DrawMesh(ObjectMesh, ObjectMaterial, transformMatrix);
        }
    }
};
}  // namespace Micro
