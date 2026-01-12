#include "CameraComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(CameraComponent) CameraComponent::CameraComponent()
    {
        m_Camera.position = MVector3{0.0f, 0.0f, 0.0f};
        m_Camera.target = MVector3{0.0f, 0.0f, 0.0f};
        m_Camera.up = MVector3{0.0f, 1.0f, 0.0f};
        m_Camera.fovy = 60.0f;
        m_Camera.projection = CAMERA_PERSPECTIVE;
    }
}  // namespace Micro