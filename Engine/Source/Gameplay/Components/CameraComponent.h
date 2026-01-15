#pragma once

#include "Component.h"

namespace Micro
{
    class GameObject;

    class CameraComponent : public Component
    {
        MICRO_COMPONENT(CameraComponent)

        explicit CameraComponent(GameObject* owner);

        MCamera3D* GetCamera() { return &m_Camera; }
        float GetFOVY() const { return m_Camera.GetFovy(); }
        void SetFOVY(float fovy) { m_Camera.SetFovy(fovy); }

        void OnLateUpdate(float deltaTime) override;

    private:
        MCamera3D m_Camera;
        TransformComponent* m_Transform;

        void SyncCameraPosition();
    };
}  // namespace Micro
