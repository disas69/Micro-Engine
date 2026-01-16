#include "CameraComponent.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Components/TransformComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(CameraComponent)
    CameraComponent::CameraComponent(GameObject* owner) : Component(owner)
    {
        m_Transform = owner->GetComponent<TransformComponent>();
        m_Camera.projection = CAMERA_PERSPECTIVE;
        m_Camera.fovy = 60.0f;
    }

    void CameraComponent::OnLateUpdate(float deltaTime)
    {
        SyncCameraPosition();
    }

    void CameraComponent::SyncCameraPosition()
    {
        if (m_Transform == nullptr)
        {
            return;
        }

        const MVector3 position = m_Transform->GetWorldPosition();
        const MVector3 forward = m_Transform->GetForward();
        const MVector3 up = m_Transform->GetUp();

        m_Camera.position = position;
        m_Camera.target = position + forward;
        m_Camera.up = up;
    }

}  // namespace Micro