#pragma once

#include "Component.h"

namespace Micro
{
    class TransformComponent : public Component
    {
        MICRO_COMPONENT(TransformComponent)

        TransformComponent();

        void SetLocalPosition(const MVector3& position);
        void SetLocalRotation(const MQuaternion& rotation);
        void SetLocalScale(const MVector3& scale);

        MVector3 GetLocalPosition() const { return m_LocalPosition; }
        MQuaternion GetLocalRotation() const { return m_LocalRotation; }
        MVector3 GetLocalScale() const { return m_LocalScale; }

        void SetWorldMatrix(const MMatrix& matrix);
        MMatrix GetWorldMatrix() const { return m_WorldMatrix; }
        MMatrix GetLocalMatrix() const;

        MVector3 GetWorldPosition() const;
        MQuaternion GetWorldRotation() const;
        MVector3 GetWorldScale() const;

        void SetParent(TransformComponent* parent);
        TransformComponent* GetParent() const { return m_Parent; }
        const std::vector<TransformComponent*>& GetChildren() const { return m_Children; }

        void MarkDirty();
        bool IsDirty() const { return m_IsDirty; }

    private:
        MMatrix m_WorldMatrix;
        std::vector<TransformComponent*> m_Children;

        MVector3 m_LocalPosition;
        MQuaternion m_LocalRotation;
        MVector3 m_LocalScale;

        TransformComponent* m_Parent = nullptr;

        bool m_IsDirty;

        void AddChild(TransformComponent* child);
        void RemoveChild(TransformComponent* child);
    };
}  // namespace Micro
