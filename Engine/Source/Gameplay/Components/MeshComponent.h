#pragma once

#include "Component.h"
#include "Serialization/Reflection/Macros.h"

namespace Micro
{
    class MeshComponent : public Component
    {
        MICRO_COMPONENT(MeshComponent)

        MeshComponent()
        {
            m_material = LoadMaterialDefault();
        }

        MMesh* GetMesh() { return &m_mesh; }
        void SetMesh(const Mesh& mesh) { m_mesh = mesh; }

        MMaterial* GetMaterial() { return &m_material; }
        void SetMaterial(const Material& material) { m_material = material; }

    private:
        MMesh m_mesh;
        MMaterial m_material;
    };
}  // namespace Micro
