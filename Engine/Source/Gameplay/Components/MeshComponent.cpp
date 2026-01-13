#include "MeshComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(MeshComponent)
    MeshComponent::MeshComponent(GameObject* owner) : Component(owner)
    {
        // Temp
        m_Mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
        m_Material = LoadMaterialDefault();
    }
}  // namespace Micro