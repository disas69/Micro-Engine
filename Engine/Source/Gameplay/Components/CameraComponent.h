#pragma once

#include "Component.h"

namespace Micro
{
    class CameraComponent : public Component
    {
        MICRO_COMPONENT(CameraComponent)

        explicit CameraComponent(GameObject* owner);

        MCamera3D* GetCamera() { return &m_Camera; }

        MVector3 GetPosition() const { return m_Camera.GetPosition(); }
        void SetPosition(const MVector3& position) { m_Camera.SetPosition(position); }

        MVector3 GetUp() const { return m_Camera.GetUp(); }
        void SetUp(const MVector3& up) { m_Camera.SetUp(up); }

        MVector3 GetTarget() const { return m_Camera.GetTarget(); }
        void SetTarget(const MVector3& target) { m_Camera.SetTarget(target); }

        float GetFOVY() const { return m_Camera.GetFovy(); }
        void SetFOVY(float fovy) { m_Camera.SetFovy(fovy); }

    private:
        MCamera3D m_Camera;
    };
}  // namespace Micro
