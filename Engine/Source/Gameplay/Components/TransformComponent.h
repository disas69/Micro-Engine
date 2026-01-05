#pragma once

#include "Component.h"

namespace Micro
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent();

        void SetParent(TransformComponent* parent);
        TransformComponent* GetParent() const { return m_parent; }
        const std::vector<TransformComponent*>& GetChildren() const { return m_children; }

        MMatrix GetWorldMatrix() const { return m_worldMatrix; }
        MMatrix GetLocalMatrix() const;

        MVector3 GetLocalPosition() const { return m_localPosition; }
        MQuaternion GetLocalRotation() const { return m_localRotation; }
        MVector3 GetLocalScale() const { return m_localScale; }

        MVector3 GetWorldPosition() const;
        MQuaternion GetWorldRotation() const;
        MVector3 GetWorldScale() const;

        void SetLocalPosition(const MVector3& position);
        void SetLocalRotation(const MQuaternion& rotation);
        void SetLocalScale(const MVector3& scale);

        void MarkDirty();
        bool IsDirty() const { return m_isDirty; }
        void SetWorldMatrix(const MMatrix& matrix)
        {
            m_worldMatrix = matrix;
            m_isDirty = false;
        }

    private:
        MVector3 m_localPosition;
        MQuaternion m_localRotation;
        MVector3 m_localScale;

        MMatrix m_worldMatrix;
        bool m_isDirty;

        TransformComponent* m_parent;
        std::vector<TransformComponent*> m_children;

        void AddChild(TransformComponent* child);
        void RemoveChild(TransformComponent* child);
    };
}  // namespace Micro
