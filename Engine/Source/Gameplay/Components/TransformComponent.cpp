#include "TransformComponent.h"
#include <algorithm>
#include "raymath.h"
#include "Serialization/Reflection/Macros.h"
#include "Serialization/Reflection/TypeDescriptor.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(
        TransformComponent,
        MICRO_FIELD(TransformComponent, m_localPosition, FieldType::Vector3),
        MICRO_FIELD(TransformComponent, m_localRotation, FieldType::Vector4),
        MICRO_FIELD(TransformComponent, m_localScale, FieldType::Vector3)
    )

    TransformComponent::TransformComponent()
        : m_localPosition(0.0f, 0.0f, 0.0f), m_localRotation(QuaternionIdentity()), m_localScale(1.0f, 1.0f, 1.0f), m_worldMatrix(MatrixIdentity()), m_isDirty(true),
          m_parent(nullptr)
    {
    }

    void TransformComponent::SetParent(TransformComponent* parent)
    {
        if (m_parent)
        {
            m_parent->RemoveChild(this);
        }

        m_parent = parent;

        if (m_parent)
        {
            m_parent->AddChild(this);
        }

        MarkDirty();
    }

    MMatrix TransformComponent::GetLocalMatrix() const
    {
        MMatrix matScale = MatrixScale(m_localScale.x, m_localScale.y, m_localScale.z);
        MMatrix matRotation = QuaternionToMatrix(m_localRotation);
        MMatrix matTranslation = MatrixTranslate(m_localPosition.x, m_localPosition.y, m_localPosition.z);

        return MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
    }

    MVector3 TransformComponent::GetWorldPosition() const
    {
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_worldMatrix, &position, &rotation, &scale);
        return position;
    }

    MQuaternion TransformComponent::GetWorldRotation() const
    {
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_worldMatrix, &position, &rotation, &scale);
        return rotation;
    }

    MVector3 TransformComponent::GetWorldScale() const
    {
        MVector3 position, scale;
        MQuaternion rotation;
        MatrixDecompose(m_worldMatrix, &position, &rotation, &scale);
        return scale;
    }

    void TransformComponent::SetLocalPosition(const MVector3& position)
    {
        m_localPosition = position;
        MarkDirty();
    }

    void TransformComponent::SetLocalRotation(const MQuaternion& rotation)
    {
        m_localRotation = rotation;
        MarkDirty();
    }

    void TransformComponent::SetLocalScale(const MVector3& scale)
    {
        m_localScale = scale;
        MarkDirty();
    }

    void TransformComponent::MarkDirty()
    {
        if (!m_isDirty)
        {
            m_isDirty = true;
            for (auto& child : m_children)
            {
                child->MarkDirty();
            }
        }
    }

    void TransformComponent::AddChild(TransformComponent* child)
    {
        m_children.push_back(child);
    }

    void TransformComponent::RemoveChild(TransformComponent* child)
    {
        m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    }
}  // namespace Micro
