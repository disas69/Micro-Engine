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

        void SetPrimitiveShape(PrimitiveShape shape);
        void SetColor(const MColor& color);

        PrimitiveShape GetPrimitiveShape() const { return m_Shape; }
        MColor GetColor() const { return m_Color; }

    private:
        void RegenerateMesh();

        PrimitiveShape m_Shape;
        MColor m_Color;
    };
}  // namespace Micro
