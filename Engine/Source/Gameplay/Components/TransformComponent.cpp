#include "TransformComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(TransformComponent, MICRO_FIELD(TransformComponent, m_LocalPosition, FieldType::Vector3),
        MICRO_FIELD(TransformComponent, m_LocalRotation, FieldType::Vector4),
        MICRO_FIELD(TransformComponent, m_LocalScale, FieldType::Vector3))
    TransformComponent::TransformComponent(GameObject* owner) : Component(owner)
    {
        m_LocalPosition = MVector3(0.0f, 0.0f, 0.0f);
        m_LocalRotation = QuaternionIdentity();
        m_LocalScale = MVector3(1.0f, 1.0f, 1.0f);
        m_WorldMatrix = MatrixIdentity();
        m_IsDirty = true;
    }

    void TransformComponent::SetParent(TransformComponent* parent)
    {
        if (m_Parent != nullptr)
        {
            m_Parent->RemoveChild(this);
        }

        m_Parent = parent;

        if (m_Parent != nullptr)
        {
            m_Parent->AddChild(this);
        }

        MarkDirty();
    }

    MMatrix TransformComponent::GetLocalMatrix() const
    {
        MMatrix matScale = MatrixScale(m_LocalScale.x, m_LocalScale.y, m_LocalScale.z);
        MMatrix matRotation = QuaternionToMatrix(m_LocalRotation);
        MMatrix matTranslation = MatrixTranslate(m_LocalPosition.x, m_LocalPosition.y, m_LocalPosition.z);
        return MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
    }

    MVector3 TransformComponent::GetWorldPosition() const
    {
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_WorldMatrix, &position, &rotation, &scale);
        return position;
    }

    MQuaternion TransformComponent::GetWorldRotation() const
    {
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_WorldMatrix, &position, &rotation, &scale);
        return rotation;
    }

    MVector3 TransformComponent::GetWorldScale() const
    {
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_WorldMatrix, &position, &rotation, &scale);
        return scale;
    }

    void TransformComponent::SetLocalPosition(const MVector3& position)
    {
        m_LocalPosition = position;
        MarkDirty();
    }

    void TransformComponent::SetLocalRotation(const MQuaternion& rotation)
    {
        m_LocalRotation = rotation;
        MarkDirty();
    }

    void TransformComponent::SetLocalScale(const MVector3& scale)
    {
        m_LocalScale = scale;
        MarkDirty();
    }

    void TransformComponent::MarkDirty()
    {
        if (!m_IsDirty)
        {
            m_IsDirty = true;
            for (auto& child : m_Children)
            {
                child->MarkDirty();
            }
        }
    }

    void TransformComponent::SetWorldMatrix(const MMatrix& matrix)
    {
        m_WorldMatrix = matrix;
        m_IsDirty = false;
    }

    void TransformComponent::AddChild(TransformComponent* child)
    {
        m_Children.push_back(child);
    }

    void TransformComponent::RemoveChild(TransformComponent* child)
    {
        m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
    }

    MVector3 TransformComponent::GetRight() const
    {
        return Vector3Normalize({m_WorldMatrix.m0, m_WorldMatrix.m1, m_WorldMatrix.m2});
    }

    MVector3 TransformComponent::GetUp() const
    {
        return Vector3Normalize({m_WorldMatrix.m4, m_WorldMatrix.m5, m_WorldMatrix.m6});
    }

    MVector3 TransformComponent::GetForward() const
    {
        return Vector3Normalize({m_WorldMatrix.m8, m_WorldMatrix.m9, m_WorldMatrix.m10});
    }

    void TransformComponent::Translate(const MVector3& delta)
    {
        m_LocalPosition += delta;
        MarkDirty();
    }

    void TransformComponent::Rotate(const MVector3& eulerAngles)
    {
        MQuaternion additionalRotation = QuaternionFromEuler(eulerAngles.x, eulerAngles.y, eulerAngles.z);
        m_LocalRotation = m_LocalRotation * additionalRotation;
        MarkDirty();
    }

    void TransformComponent::LookAt(const MVector3& target)
    {
        MMatrix lookAtMatrix = MatrixLookAt(GetWorldPosition(), target, GetUp());
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(lookAtMatrix, &position, &rotation, &scale);
        SetLocalRotation(rotation);
    }

    void TransformComponent::ForEachChild(const std::function<void(TransformComponent*)>& func) const
    {
        for (const auto child : m_Children)
        {
            func(child);
        }
    }
}  // namespace Micro
