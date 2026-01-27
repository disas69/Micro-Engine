#pragma once

#include "Component.h"

namespace Micro
{
    class MeshComponent : public Component
    {
        MICRO_COMPONENT(MeshComponent)

        explicit MeshComponent(GameObject* owner);

        MMesh* GetMesh() { return &m_Mesh; }
        void SetMesh(const Mesh& mesh) { m_Mesh = mesh; }

        MMaterial* GetMaterial() { return &m_Material; }
        void SetMaterial(const Material& material) { m_Material = material; }

    protected:
        MMesh m_Mesh;
        MMaterial m_Material;
    };
}  // namespace Micro
