#include "MeshComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(MeshComponent) MeshComponent::MeshComponent()
    {
        // Temp
        m_Mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
        m_Material = LoadMaterialDefault();
    }
}  // namespace Micro