#pragma once

#include "MeshComponent.h"
#include "PrimitiveShape.h"

namespace Micro
{
    class PrimitiveMeshComponent : public MeshComponent
    {
        MICRO_COMPONENT(PrimitiveMeshComponent)

        explicit PrimitiveMeshComponent(GameObject* owner);
        PrimitiveMeshComponent(GameObject* owner, PrimitiveShape shape, MColor color);

        PrimitiveShape GetPrimitiveShape() const { return m_Shape; }
        MColor GetColor() const { return m_Color; }

        void OnCreate() override;
        void OnDeserialize() override;

        void SetPrimitiveShape(PrimitiveShape shape);
        void SetColor(const MColor& color);

    private:
        void RegenerateMesh();

        PrimitiveShape m_Shape = PrimitiveShape::Plane;
        MColor m_Color = MColor::White();
    };
}  // namespace Micro
