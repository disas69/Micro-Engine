#pragma once

#include "Component.h"

namespace Micro
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent()
        {
            m_camera.position = MVector3{0.0f, 0.0f, 0.0f};
            m_camera.target = MVector3{0.0f, 0.0f, 0.0f};
            m_camera.up = MVector3{0.0f, 1.0f, 0.0f};
            m_camera.fovy = 60.0f;
            m_camera.projection = CAMERA_PERSPECTIVE;
        }

        MCamera3D* GetCamera() { return &m_camera; }

        MVector3 GetPosition() const { return m_camera.GetPosition(); }
        void SetPosition(const MVector3& position) { m_camera.SetPosition(position); }

        MVector3 GetUp() const { return m_camera.GetUp(); }
        void SetUp(const MVector3& up) { m_camera.SetUp(up); }

        MVector3 GetTarget() const { return m_camera.GetTarget(); }
        void SetTarget(const MVector3& target) { m_camera.SetTarget(target); }

        float GetFOVY() const { return m_camera.GetFovy(); }
        void SetFOVY(float fovy) { m_camera.SetFovy(fovy); }

    private:
        MCamera3D m_camera;
    };
}  // namespace Micro
