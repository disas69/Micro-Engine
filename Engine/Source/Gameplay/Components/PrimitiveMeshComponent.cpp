#include "PrimitiveMeshComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(PrimitiveMeshComponent,
        MICRO_FIELD(PrimitiveMeshComponent, m_Shape, FieldType::Enum),
        MICRO_FIELD(PrimitiveMeshComponent, m_Color, FieldType::Color))
    PrimitiveMeshComponent::PrimitiveMeshComponent(GameObject* owner) : MeshComponent(owner)
    {
    }

    PrimitiveMeshComponent::PrimitiveMeshComponent(GameObject* owner, PrimitiveShape shape, MColor color) : MeshComponent(owner), m_Shape(shape), m_Color(color)
    {
    }

    void PrimitiveMeshComponent::OnCreate()
    {
        MeshComponent::OnCreate();
        RegenerateMesh();
    }

    void PrimitiveMeshComponent::OnDeserialize()
    {
        MeshComponent::OnDeserialize();
        RegenerateMesh();
    }

    void PrimitiveMeshComponent::SetPrimitiveShape(PrimitiveShape shape)
    {
        if (m_Shape != shape)
        {
            m_Shape = shape;
            RegenerateMesh();
        }
    }

    void PrimitiveMeshComponent::SetColor(const MColor& color)
    {
        m_Color = color;
        m_Material.maps[MATERIAL_MAP_DIFFUSE].color = m_Color;
    }

    void PrimitiveMeshComponent::RegenerateMesh()
    {
        switch (m_Shape)
        {
            case PrimitiveShape::Plane: m_Mesh = GenMeshPlane(10.0f, 10.0f, 1, 1); break;
            case PrimitiveShape::Cube: m_Mesh = GenMeshCube(1.0f, 1.0f, 1.0f); break;
            case PrimitiveShape::Sphere: m_Mesh = GenMeshSphere(1.0f, 16, 16); break;
            case PrimitiveShape::Cylinder: m_Mesh = GenMeshCylinder(1.0f, 2.0f, 16); break;
            case PrimitiveShape::Cone: m_Mesh = GenMeshCone(1.0f, 2.0f, 16); break;
            case PrimitiveShape::Torus: m_Mesh = GenMeshTorus(0.5f, 1.0f, 16, 32); break;
        }

        m_Material = LoadMaterialDefault();
        m_Material.maps[MATERIAL_MAP_DIFFUSE].color = m_Color;
    }
}  // namespace Micro
