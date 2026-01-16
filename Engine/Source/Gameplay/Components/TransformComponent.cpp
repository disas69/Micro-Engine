#include "TransformComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(TransformComponent, MICRO_FIELD(TransformComponent, m_LocalPosition, FieldType::Vector3),
        MICRO_FIELD(TransformComponent, m_LocalRotation, FieldType::Vector4), MICRO_FIELD(TransformComponent, m_LocalScale, FieldType::Vector3))
    TransformComponent::TransformComponent(GameObject* owner) : Component(owner)
    {
        m_LocalPosition = MVector3(0.0f, 0.0f, 0.0f);
        m_LocalRotation = QuaternionIdentity();
        m_LocalScale = MVector3(1.0f, 1.0f, 1.0f);
        m_WorldMatrix = MatrixIdentity();
        m_IsDirty = true;
    }

    void TransformComponent::OnDestroy()
    {
        SetParent(nullptr);

        for (auto& child : m_Children)
        {
            child->SetParent(nullptr);
        }

        m_Children.clear();
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

    MVector3 TransformComponent::GetWorldPosition()
    {
        ForceUpdateWorldMatrix();
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_WorldMatrix, &position, &rotation, &scale);
        return position;
    }

    MQuaternion TransformComponent::GetWorldRotation()
    {
        ForceUpdateWorldMatrix();
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_WorldMatrix, &position, &rotation, &scale);
        return rotation;
    }

    MVector3 TransformComponent::GetWorldScale()
    {
        ForceUpdateWorldMatrix();
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

    MVector3 TransformComponent::GetRight()
    {
        return Vector3RotateByQuaternion({1, 0, 0}, GetWorldRotation());
    }

    MVector3 TransformComponent::GetUp()
    {
        return Vector3RotateByQuaternion({0, 1, 0}, GetWorldRotation());
    }

    MVector3 TransformComponent::GetForward()
    {
        return Vector3RotateByQuaternion({0, 0, -1}, GetWorldRotation());
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
        const MVector3 position = GetWorldPosition();

        MMatrix view = MatrixLookAt(position, target, GetUp());
        MMatrix worldRot = MatrixInvert(view);

        MQuaternion worldRotation = QuaternionFromMatrix(worldRot);

        if (m_Parent != nullptr)
        {
            worldRotation = QuaternionMultiply(
                QuaternionInvert(m_Parent->GetWorldRotation()),
                worldRotation
            );
        }

        SetLocalRotation(worldRotation);
    }

    void TransformComponent::ForEachChild(const std::function<void(TransformComponent*)>& func) const
    {
        for (const auto child : m_Children)
        {
            func(child);
        }
    }

    void TransformComponent::AddChild(TransformComponent* child)
    {
        m_Children.push_back(child);
    }

    void TransformComponent::RemoveChild(TransformComponent* child)
    {
        m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
    }

    void TransformComponent::ForceUpdateWorldMatrix()
    {
        if (m_IsDirty)
        {
            if (m_Parent != nullptr)
            {
                m_Parent->ForceUpdateWorldMatrix();
                m_WorldMatrix = MatrixMultiply(m_Parent->m_WorldMatrix, GetLocalMatrix());
            }
            else
            {
                m_WorldMatrix = GetLocalMatrix();
            }

            m_IsDirty = false;
        }
    }
}  // namespace Micro
