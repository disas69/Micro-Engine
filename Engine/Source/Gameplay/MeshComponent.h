#pragma once

#include "GraphicComponent.h"
#include "Transform2DComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include <raylib.h>
#include <raymath.h>

namespace Micro
{
class MeshComponent : public GraphicComponent
{
public:
    raylib::Mesh ObjectMesh = {};
    raylib::Material ObjectMaterial = {};

    MeshComponent() : GraphicComponent(GraphicComponentType::GraphicType3D) { ObjectMaterial = LoadMaterialDefault(); }

    void OnRender() override
    {
        raylib::Matrix transformMatrix = MatrixIdentity();

        auto transform3d = m_owner->GetComponent<TransformComponent>();
        if (transform3d != nullptr)
        {
            transformMatrix = transform3d->GetTransformMatrix();
        }
        else
        {
            auto transform2d = m_owner->GetComponent<Transform2DComponent>();
            if (transform2d != nullptr)
            {
                Matrix matScale = MatrixScale(transform2d->Scale.x, transform2d->Scale.y, 1.0f);
                Matrix matRotation = MatrixRotateZ(transform2d->Rotation * DEG2RAD);
                Matrix matTranslation = MatrixTranslate(transform2d->Position.x, transform2d->Position.y, 0.0f);

                transformMatrix = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
            }
        }

        if (ObjectMesh.vertexCount > 0)
        {
            DrawMesh(ObjectMesh, ObjectMaterial, transformMatrix);
        }
    }
};
}  // namespace Micro
