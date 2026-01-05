#pragma once

#include "Component.h"

namespace Micro
{
    class MeshComponent : public Component
    {
    public:
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
